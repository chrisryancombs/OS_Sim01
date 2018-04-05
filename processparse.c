// Code Implementation File Information /////////////////////////////
/**
* @file processparse.c
*
* @brief Implementation file for processparse code
*
* @details Implements all functions of the processparse utilities
*
*
* @version 1.00
* C.S. Student ( 2 February 2018 )
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

// Free Function Implementation
/**
* @brief constructPCB creates a PCB Linked list from a metadata linked list
*
* @details Reads in a metadata linked list and stores each node
* (if necessary) in a correspinding PCB Node.
*
* @pre struct Metadata contains a metadata linked list
*
* @post struct PCB contains all values parsed for in metadata llist
* as well as the next start node from the metadata linked list
*
*/

struct PCB *constructPCB( struct Metadata *metadata )
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
            currentPCB->state = 0;

            currentPCB->nextProcess = malloc( sizeof( struct PCB ) );
            currentPCB = currentPCB->nextProcess;
        }
        currentMD = currentMD->nextNode;
    }
    currentPCB = NULL;
    free(currentPCB);
    // printPCB(PCBHead);

    return PCBHead;
}

void executeProcesses( struct Config config, struct Metadata *metadata )
{
    // Open file and allocate
    FILE *outFile = fopen( config.logFilepath, "w" );
    char* time = malloc( STR_MAX );

    // Set bools for printing options
    int toConsole = 0, toFile = 0;
    if( stringCompare( config.logTo, "Monitor" ) == 0 ) toConsole = 1;
    else if( stringCompare( config.logTo, "File" ) == 0 ) toFile = 1;
    else // Both
    {
        toConsole = 1;
        toFile = 1;
    }

    // File Header
    char *tempString = malloc(STR_MAX);
    char *tempString2 = malloc(STR_MAX);

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

    // Contruct Schedule from metadata linked list
    struct PCB *PCBHead = constructPCB( metadata );
    struct PCB *currentPCB = PCBHead;

    accessTimer( LAP_TIMER, time );
    sprintf( tempString,  "Time:  %s, OS: All proccesses initialized in New state\n", time );
    logMessage( tempString, toFile, toConsole, outFile );

    // Set all Processes to Ready
    while ( currentPCB->process != NULL)
    {
        currentPCB->state = READY;
        currentPCB = currentPCB->nextProcess;
    }
    accessTimer( LAP_TIMER, time );
    sprintf( tempString, "Time:  %s, OS: All proccesses now set in Ready state\n", time );
    logMessage( tempString, toFile, toConsole, outFile );

    currentPCB = PCBHead;
    while ( currentPCB->process != NULL )
    {
        accessTimer( LAP_TIMER, time );
        sprintf( tempString, "Time:  %s, OS: FCFS-N Strategy selects Process %d\n", time, currentPCB->index );
        logMessage( tempString, toFile, toConsole, outFile );

        accessTimer( LAP_TIMER, time);
        sprintf( tempString, "Time:  %s, OS: Process %d set in Running state\n", time, currentPCB->index );
        logMessage( tempString, toFile, toConsole, outFile );

        struct Metadata *currentOp = currentPCB->process;
        while( stringCompare( currentOp->command, "end" ) != 0 )
        {
            switch ( currentOp->letter )
            {
                accessTimer( LAP_TIMER, time );
                case ( 'M' ):
                    sprintf( tempString, "Time:  %s, Process %d, Memory management allocate action start\n", time, currentPCB->index );
                    runTimer(100);
                    accessTimer( LAP_TIMER, time );
                    sprintf( tempString2, "Time:  %s, Process %d, Memory management allocate action end\n", time, currentPCB->index );
                    break;

                case ( 'I' ):
                    sprintf( tempString, "Time:  %s, Process %d, %s input start\n", time, currentPCB->index, currentOp->command );
                    runTimer( config.ioTime );
                    accessTimer( LAP_TIMER, time );
                    sprintf( tempString2, "Time:  %s, Process %d, %s input end\n", time, currentPCB->index, currentOp->command );
                    break;

                case ( 'O' ):
                    sprintf( tempString, "Time:  %s, Process %d, %s output start\n", time, currentPCB->index, currentOp->command );
                    runTimer( config.ioTime );
                    accessTimer( LAP_TIMER, time );
                    sprintf( tempString2, "Time:  %s, Process %d, %s output end\n", time, currentPCB->index, currentOp->command );
                    break;

                case ( 'P' ):
                    sprintf( tempString, "Time:  %s, Run operation start\n", time );
                    runTimer( config.processorTime );
                    accessTimer( LAP_TIMER, time );
                    sprintf( tempString2, "Time:  %s, Run operation end\n", time );
                    break;
            }
            currentOp = currentOp->nextNode;
            logMessage( tempString, toFile, toConsole, outFile );
            logMessage( tempString2, toFile, toConsole, outFile );
        }

        accessTimer( LAP_TIMER, time );
        currentPCB->state = EXIT;
        sprintf( tempString, "Time:  %s, OS: Process %d set in Exit state\n", time, currentPCB->index );
        logMessage( tempString, toFile, toConsole, outFile );
        currentPCB = currentPCB->nextProcess;
    }

    accessTimer( LAP_TIMER, time );
    sprintf( tempString, "Time:  %s, System stop\n", time);
    logMessage( tempString, toFile, toConsole, outFile );

    deletePCB( PCBHead );
    fclose(outFile);

    free( tempString );
    free( tempString2 );
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

    while( current != NULL )
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
    if( toConsole ) printf( "%s", message );
    if( toFile ) fprintf( file, "%s", message );
}

// Preprocessor
#endif
