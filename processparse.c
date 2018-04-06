// Code Implementation File Information /////////////////////////////
/**
* @file processparse.c
*
* @brief Implementation file for processparse code
*
* @details Implements all functions of the processparse utilities
*
*
* @version 1.03
* C.S. Student ( 6 April 2018 )
* Initial development and testing of processparse code
*
* @note Requires processparse.h
*/

// Preprocessor
#ifndef PROCESSPARSE_C
#define PROCESSPARSE_C

// Header Files
#include "processparse.h"

// Global Constant Definitions
const int STR_MAX = 1024;

// constructPCB - creates a PCB Linked list from a metadata linked list
// input: Metadata* metadata -  contains a metadata linked list
// output: PCB return - contains all values parsed for in metadata llist
//         as well as the next start node from the metadata linked list
struct PCB *constructPCB( struct Metadata *metadata, struct Config config )
{
    int index = 0;
    struct Metadata *currentMD = metadata;
    struct PCB *PCBHead = malloc( sizeof( struct PCB ) );
    struct PCB *currentPCB = PCBHead;

    while ( currentMD != NULL )
    {
        if ( currentMD->letter == 'A' && stringCompare( currentMD->command, "start") == 0 )
        {
            currentPCB->index = index++;
            currentPCB->process = currentMD;
            currentPCB->time = calcProcessTime( currentPCB );
            currentPCB->state = 0;

            currentPCB->nextProcess = malloc( sizeof( struct PCB ) );
            currentPCB = currentPCB->nextProcess;
        }
        currentMD = currentMD->nextNode;
    }
    currentPCB = NULL;
    free( currentPCB );

    if( stringCompare(config.cpuSchedulingCode, "SJF-N") == 0 )
    {
        PCBHead = bubbleSort(PCBHead);
    }

    printPCB(PCBHead);
    return PCBHead;
}

// bubbleSort - sorts a PCB from least to greatest processing time
// input: PCB *firstNode: Head of PCB to be Sorted
// output: PCB *return: Sorted PCB, for use with SJF-N
struct PCB *bubbleSort( struct PCB *firstNode )
{
    int tempIndex;
    int tempTime;
    struct Metadata *tempMetadata;

    struct PCB *currentNode = NULL;
    int cont = 1;
    while ( cont ) // Only continue if swaps are necessary
    {
        cont = 0;
        currentNode = firstNode;

        while( currentNode->nextProcess->process != NULL)
        {
            if( currentNode->time > currentNode->nextProcess->time )
            {
                //create temps and swap
                tempIndex = currentNode->index;
                tempMetadata = currentNode->process;
                tempTime = currentNode->time;

                currentNode->index = currentNode->nextProcess->index;
                currentNode->process = currentNode->nextProcess->process;
                currentNode->time = currentNode->nextProcess->time;

                currentNode->nextProcess->index = tempIndex;
                currentNode->nextProcess->process = tempMetadata;
                currentNode->nextProcess->time = tempTime;
                cont = 1;
            }
            currentNode = currentNode->nextProcess;
        }

    }
    // printPCB(firstNode->nextProcess);
    return firstNode->nextProcess;
}


// calcProcessTime - sums of total processing time for a Process
// input: PCB *pcb - Head of Process
// output: int return - processing time sum
int calcProcessTime( struct PCB *pcb )
{
    struct Metadata *current = pcb->process;
    int processTime = 0;

    while( stringCompare( current->command, "end" ) != 0 )
    {
        processTime += current->time;
        current = current->nextNode;
    }
    return processTime;
}

// runThread - spawns a thread and runs for the given amount of time
// input: void *arg - pointer to int that will be cast as run time
void *runThread( void  *arg )
{
    int runTime = *( (int *) arg ); // evil
    runTimer( runTime );
    pthread_exit( 0 );
}

// memManage - spawns a thread and tried to manage memory
// input: void *arg - pointer to the MMU holding the process
void *memManage( void  *arg )
{
    struct MMU *mmu = ( (struct MMU *) arg );
    if( stringCompare( mmu->process->command , "allocate" ) == 0)
    {
        mmu->request = mmu->process->number % 1000;
        int remain = mmu->process->number /= 1000;
        mmu->base = remain % 1000;
        mmu->segment = remain /= 1000;

        if( (mmu->base + mmu->segment) > mmu->maxMem)
        {
            mmu->failure = 1;
        }
    }
    else // "access"
    {
        int request = mmu->process->number % 1000;
        int remain = mmu->process->number /= 1000;
        int segment = remain /= 1000;

        if( (request + segment) > mmu->request + (mmu->segment) )
        {
            mmu->failure = 1;
        }
    }
    pthread_exit( 0 );
}

// executeProcesses - iterates through and runs all processes in a PCB
// input: Config config - data read from config file specified when run
// input Metadata metadata - data read from metadata file listed in config
void executeProcesses( struct Config config, struct Metadata *metadata )
{
    // Set bools for printing options
    int toConsole = 0;
    int toFile = 0;
    if( stringCompare( config.logTo, "Monitor" ) == 0 )
    {
        toConsole = 1;
    }
    else if( stringCompare( config.logTo, "File" ) == 0 )
    {
        toFile = 1;
    }
    else // Both
    {
        toConsole = 1;
        toFile = 1;
    }

    // File Header
    FILE *outFile = NULL;
    if( toFile )
    {
        outFile = fopen( config.logFilepath, "w" );
    }
    writeHeader( config, toFile, toConsole, outFile );

    // Contruct Schedule from metadata linked list
    struct PCB *PCBHead = constructPCB( metadata, config );
    struct PCB *currentPCB = PCBHead;

    char *tempString = malloc( STR_MAX );
    char *tempString2 = malloc( STR_MAX );
    char* time = malloc( STR_MAX );
    accessTimer( LAP_TIMER, time );
    sprintf( tempString,  "Time:  %s, OS: All proccesses initialized in New state\n", time );
    logMessage( tempString, toFile, toConsole, outFile );

    // Set all Processes to Ready
    while ( currentPCB->process != NULL )
    {
        currentPCB->state = READY;
        currentPCB = currentPCB->nextProcess;
    }
    accessTimer( LAP_TIMER, time );
    sprintf( tempString, "Time:  %s, OS: All proccesses now set in Ready state\n", time );
    logMessage( tempString, toFile, toConsole, outFile );

    // Initialize MMU
    struct MMU *mmu = malloc( sizeof( struct MMU ) );
    mmu->maxMem = config.memoryAvailable;
    mmu->segment = 0;
    mmu->request = 0;
    mmu->failure = 0;
    mmu->process = NULL;

    // Run processes
    pthread_t thread;
    currentPCB = PCBHead;
    struct Metadata *currentOp;
    while ( currentPCB->process != NULL )
    {
        accessTimer( LAP_TIMER, time );
        sprintf( tempString, "Time:  %s, OS: %s Strategy selects Process %d with time: %d mSec\n", time, config.cpuSchedulingCode, currentPCB->index, currentPCB->time );
        logMessage( tempString, toFile, toConsole, outFile );

        accessTimer( LAP_TIMER, time);
        sprintf( tempString, "Time:  %s, OS: Process %d set in Running state\n", time, currentPCB->index );
        logMessage( tempString, toFile, toConsole, outFile );
        currentOp = currentPCB->process;

        // Iterate through metadata nodes in process
        int *arg = malloc( sizeof( *arg ) );
        while( stringCompare( currentOp->command, "end" ) != 0 )
        {
            // Prepare output Strings, end time will be prepended after thread runs
            accessTimer( LAP_TIMER, time );
            switch( currentOp->letter )
            {
                case ( 'M' ):
                    sprintf( tempString, "Time:  %s, Process %d, MMU %s start\n", time, currentPCB->index, currentOp->command );
                    sprintf( tempString2, "Process %d, MMU %s end:", currentPCB->index, currentOp->command );
                    break;

                case ( 'I' ):
                    sprintf( tempString, "Time:  %s, Process %d, %s input start\n", time, currentPCB->index, currentOp->command );
                    sprintf( tempString2, "Process %d, %s input end", currentPCB->index, currentOp->command );
                    break;

                case ( 'O' ):
                    sprintf( tempString, "Time:  %s, Process %d, %s output start\n", time, currentPCB->index, currentOp->command );
                    sprintf( tempString2, "Process %d, %s output end", currentPCB->index, currentOp->command );
                    break;

                case ( 'P' ):
                    sprintf( tempString, "Time:  %s, Process %d, Run operation start\n", time, currentPCB->index );
                    sprintf( tempString2,"Process %d, Run operation end", currentPCB->index );
                    break;
            }

            if( currentOp->letter != 'A' && currentOp->letter != 'S' )
            {
                logMessage( tempString, toFile, toConsole, outFile );
                if( currentOp->letter == 'M' ) // Handle memory management
                {
                    mmu->process = currentOp;
                    pthread_create(&thread, NULL, memManage, (void *)mmu);
                    pthread_join(thread, NULL);
                    if( mmu->failure )
                    {
                        accessTimer( LAP_TIMER, time );
                        sprintf( tempString, "Time:  %s, %s Failed\n", time, tempString2);
                        logMessage( tempString, toFile, toConsole, outFile );
                        mmu->failure = 0;
                    }
                    else
                    {
                        accessTimer( LAP_TIMER, time );
                        sprintf( tempString, "Time:  %s, %s Success\n", time, tempString2);
                        logMessage( tempString, toFile, toConsole, outFile );
                    }
                }
                else // Spawn thread and run the clock
                {
                    *arg = currentOp->time;
                    pthread_create(&thread, NULL, runThread, arg);
                    pthread_join(thread, NULL);

                    // Append time to beginning of end string
                    accessTimer( LAP_TIMER, time );
                    sprintf( tempString, "Time:  %s, %s\n", time, tempString2);
                    logMessage( tempString, toFile, toConsole, outFile );
                }

            }
            currentOp = currentOp->nextNode;
        }

        accessTimer( LAP_TIMER, time );
        currentPCB->state = EXIT;
        sprintf( tempString, "Time:  %s, OS: Process %d set in Exit state\n", time, currentPCB->index );
        logMessage( tempString, toFile, toConsole, outFile );
        currentPCB = currentPCB->nextProcess;
        free( arg );
    }

    accessTimer( LAP_TIMER, time );
    sprintf( tempString, "Time:  %s, System stop\n", time);
    logMessage( tempString, toFile, toConsole, outFile );

    deletePCB( PCBHead );

    if( toFile ){
        fclose(outFile);
    }

    free( tempString );
    free( tempString2 );
    free( time );
}

// writeHeader - writes simulation header to file, only used once, but looks NICER
// input: Config config - config file use for output options
// input: int toFile - bool whether to print to file
// input: into toConsole - bool whether to print to to console
// input: FILE *outFile - possible file to print to
void writeHeader(struct Config config, int toFile, int toConsole, FILE *outFile)
{
    char *tempString = malloc(STR_MAX);
    char *time = malloc(STR_MAX);

    sprintf( tempString, "OS Simulation 2\n===================\n" );
    logMessage( tempString, toFile, toConsole, outFile );

    sprintf( tempString, "Using metadata file: %s\n", config.filepath );
    logMessage( tempString, toFile, toConsole, outFile );

    sprintf( tempString, "Using log file:      %s\n===================\n", config.logFilepath );
    logMessage( tempString, toFile, toConsole, outFile );

    accessTimer(ZERO_TIMER, time);
    sprintf( tempString, "Time:  %s, System Start\n", time );
    logMessage( tempString, toFile, toConsole, outFile );

    accessTimer(LAP_TIMER, time);
    sprintf( tempString, "Time:  %s, OS: Begin PCB Creation\n", time );
    logMessage( tempString, toFile, toConsole, outFile );

    free( tempString );
    free( time );
}

// printPCB - iterates through and prints all processes in a PCB
// input: head of linked list PCB
void printPCB( struct PCB *head )
{
    struct PCB *current = head;
    while( current->process != NULL )
    {
        fprintf( stderr, "Process -------------\n" );
        fprintf( stderr, "index: %d\n", current->index );
        fprintf( stderr, "time: %d\n", current->time );
        fprintf( stderr, "state: %d\n", current->state );
        fprintf( stderr, "letter: %c\n", current->process->letter );
        fprintf( stderr, "command: %s\n", current->process->command );
        current = current->nextProcess;
    }
}

// deletePCB - iterates through and deletes all processes in a PCB
// input: head of linked list PCB
void deletePCB( struct PCB *head )
{
    struct PCB *current = head;
    struct PCB *nextNode;

    while( current->process != NULL )
    {
        nextNode = current->nextProcess;
        free( current );
        current = nextNode;
    }
}

// logMessage - prints to console and/or file
// input: char *message - string to be printed
// input: int toFile    - bool for print to file
// input: int toConsole - bool for print to toConsole
// input: FILE *file    - pointer to output log file
void logMessage( char *message, int toFile, int toConsole, FILE *file)
{
    if( toConsole )
    {
        printf( "%s", message );
    }

    if( toFile )
    {
        fprintf( file, "%s", message );
    }
}

// Preprocessor
#endif
