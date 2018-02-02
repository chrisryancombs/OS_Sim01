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
    struct config
    {
      int version;
      char *filepath;
      char *cpu_scheduling_code;
      int quantum_time;
      int memory_available;
      int processor_time;
      int io_time;
      char *log_to;
      char *log_filepath;
    };
//
// Free Function Prototypes ///////////////////////////////////////
//
    struct config read_config(const char *filename);
    void print_config(struct config config_values);
