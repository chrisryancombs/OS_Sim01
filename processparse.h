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

// Data Structure Definitions
struct PCB
{
    int index;
    struct Metadata *process;
    enum { NEW, READY, RUNNING, BLOCKED, EXIT } state;
    struct PCB *nextProcess;
};

// Free Function Prototypes 
struct PCB *constructPCB( struct Metadata *metadata );
void executeProcesses( struct Config config, struct Metadata *metadata );
void deletePCB( struct PCB *head );
void printPCB( struct PCB *head );

#endif
