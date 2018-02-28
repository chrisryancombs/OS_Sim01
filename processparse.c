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

// Header Files ///////////////////////////////////////////////////
//
    #include "processparse.h"
//
// Global Constant Definitions ////////////////////////////////////
//
    const int STR_MAX = 1024;
// Free Function Implementation ///////////////////////////////////
//
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
        FILE *outFile = fopen( config.logFilepath, "w" );

        char* time = malloc( STR_MAX );
        fprintf( outFile, "OS Simulation 2\n" );
        fprintf( outFile, "===================\n" );
        fprintf( outFile, "Using metadata file: %s\n", config.filepath );
        fprintf( outFile, "Using log file:      %s\n", config.logFilepath );
        fprintf( outFile, "===================\n" );

        accessTimer(ZERO_TIMER, time);
        fprintf( outFile, "Time:  %s, System Start\n", time );
        accessTimer(GET_TIME, time);
        fprintf( outFile, "Time:  %s, OS: Begin PCB Creation\n", time );

        // Contruct Schedule from metadata linked list
        struct PCB *PCBHead = constructPCB( metadata );
        struct PCB *currentPCB = PCBHead;
        accessTimer( GET_TIME, time );
        fprintf( outFile,  "Time:  %s, OS: All proccesses initialized in New state\n", time );

        // Set all Processes to Ready
        while ( currentPCB->process != NULL)
        {
            currentPCB->state = READY;
            currentPCB = currentPCB->nextProcess;
        }
        accessTimer( GET_TIME, time );
        fprintf( outFile, "Time:  %s, OS: All proccesses now set in Ready state\n", time );

        currentPCB = PCBHead;
        while ( currentPCB->process != NULL )
        {
            accessTimer( GET_TIME, time );
            fprintf( outFile, "Time:  %s, OS: FCFS-N Strategy selects Process %d\n", time, currentPCB->index );

            accessTimer( GET_TIME, time);
            fprintf( outFile, "Time:  %s, OS: Process %d set in Running state\n", time, currentPCB->index );

            struct Metadata *currentOp = currentPCB->process;
            while( stringCompare( currentOp->command, "end" ) != 0 )
            {
                switch ( currentOp->letter )
                {
                    case ( 'M' ):
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Process %d, Memory management allocate action start\n", time, currentPCB->index );
                        runTimer(100);
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Process %d, Memory management allocate action end\n", time, currentPCB->index );
                        break;

                    case ( 'I' ):
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Process %d, %s input start\n", time, currentPCB->index, currentOp->command );
                        runTimer( config.ioTime );
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Process %d, %s input end\n", time, currentPCB->index, currentOp->command );
                        break;

                    case ( 'O' ):
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Process %d, %s output start\n", time, currentPCB->index, currentOp->command );
                        runTimer( config.ioTime );
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Process %d, %s output end\n", time, currentPCB->index, currentOp->command );
                        break;

                    case ( 'P' ):
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Run operation start\n", time );
                        runTimer( config.processorTime );
                        accessTimer( GET_TIME, time );
                        fprintf( outFile, "Time:  %s, Run operation end\n", time );
                        break;
                }
                currentOp = currentOp->nextNode;
            }

            accessTimer( GET_TIME, time );
            currentPCB->state = EXIT;
            fprintf( outFile, "Time:  %s, OS: Process %d set in Exit state\n", time, currentPCB->index );
            currentPCB = currentPCB->nextProcess;
        }

        accessTimer( GET_TIME, time );
        fprintf( outFile, "Time:  %s, System stop\n", time);

        deletePCB( PCBHead );
        fclose(outFile);

        if (stringCompare(config.logTo, "Monitor") == 0 || stringCompare(config.logTo, "Both") == 0)
        {
            // I know this is disgusting and a hack but idc i wrote it in five minutes
            FILE *out = fopen( config.logFilepath, "r" );
            char line[STR_MAX];
            while( fgets( line, STR_MAX, out ) != NULL)
            {
                printf("%s", line);
            }
            fclose(out);
        }

        if (stringCompare(config.logTo, "Monitor") == 0 )
        {
            remove( config.logFilepath );
        }

    }

//
// Free Function Implementation ///////////////////////////////////
//
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

//
// Free Function Implementation ///////////////////////////////////
//
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
