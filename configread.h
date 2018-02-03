// Header File Information /////////////////////////////////////
/**
* @file configread.h
*
* @brief Header file for configread code
*
* @details Specifies functions, constants, and other information
 * related to the configread code
*
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing of configread code
*
* @note None
*/

// Header Files ///////////////////////////////////////////////////
//
    #include "utilities.h"
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
    struct Config
    {
      int version;
      char *filepath;
      char *cpuSchedulingCode;
      int quantumTime;
      int memoryAvailable;
      int processorTime;
      int ioTime;
      char *logTo;
      char *logFilepath;
    };
//
// Free Function Prototypes ///////////////////////////////////////
//
    struct Config readConfig(const char *filename);
    void printConfig(struct Config configValues);
