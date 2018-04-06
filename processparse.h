// Header File Information /////////////////////////////////////
/**
* @file processparse.h
*
* @brief Header file for processparse code
*
* @details Specifies functions, constants, and other information
* related to the processparse code
*
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing of processparse code
*
* @note None
*/

// Precompiler
#ifndef PROCESSPARSE_H
#define PROCESSPARSE_H

// Header Files
#include "utilities.h"
#include "metaread.h"
#include "configread.h"
#include "simtimer.h"

#include <pthread.h>

// Data Structure Definitions
struct PCB
{
    int index;
    int time;
    struct Metadata *process;
    enum { NEW, READY, RUNNING, BLOCKED, EXIT } state;
    struct PCB *nextProcess;
};

struct MMU
{
    int maxMem;
    int failure;
    int segment;
    int base;
    int request;
    struct Metadata *process;
};

enum{ FCFS, SJF } scheduling;

// Free Function Prototypes
struct PCB *constructPCB( struct Metadata *metadata, struct Config config );
struct PCB *bubbleSort( struct PCB *firstNode );
int calcProcessTime( struct PCB *pcb );
void executeProcesses( struct Config config, struct Metadata *metadata );
void deletePCB( struct PCB *head );
void printPCB( struct PCB *head );
void logMessage( char *message, int toFile, int toConsole, FILE *file);
void *runThread( void *time );
void writeHeader(struct Config config, int toFile, int toConsole, FILE *outFile);

#endif
