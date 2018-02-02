// Header File Information /////////////////////////////////////
/**
* @file metaread.h
*
* @brief Header file for metaread code
*
* @details Specifies functions, constants, and other information
* related to the metaread code
*
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing of metaread code
*
* @note None
*/



// Header Files ///////////////////////////////////////////////////
//
    #include <stdio.h>
    #include <stdlib.h>

    #include "utilities.h"
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
    struct metadata
    {
      char letter;
      char *command;
      int number;
      struct metadata *nextnode;

    };
//
// Free Function Prototypes ///////////////////////////////////////
//
    struct metadata *read_metadata(const char *filename);
    struct metadata *create_metadata_node(char *string);
    void push_metadata_node(struct metadata *head, struct metadata *node);
    void print_metadata(struct metadata *head);
