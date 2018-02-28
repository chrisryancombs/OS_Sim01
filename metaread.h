#ifndef METAREAD_H
#define METAREAD_H

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
    #include "utilities.h"
//
// Data Structure Definitions (structs, enums, etc.)////////////////
//
    struct Metadata
    {
      char letter;
      char *command;
      int number;
      struct Metadata *nextNode;

    };
//
// Free Function Prototypes ///////////////////////////////////////
//
    struct Metadata *readMetadata(const char *filename);
    struct Metadata *createMetadataNode(char *string);
    void pushMetadataNode(struct Metadata *head, struct Metadata *node);
    void printMetadata(struct Metadata *head);
    void deleteMetadata(struct Metadata *head);

#endif
