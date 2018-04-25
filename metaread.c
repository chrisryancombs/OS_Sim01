// Code Implementation File Information /////////////////////////////
/**
* @file metaread.c
*
* @brief Implementation file for metaread code
*
* @details Implements all functions of the metaread utilities
*
*
* @version 1.00
* C.S. Student ( 2 February 2018 )
* Initial development and testing of metaread code
*
* @note Requires metaread.h
*/

// Precompiler
#ifndef METAREAD_C
#define METAREAD_C

// Header Files
#include "metaread.h"

// Global Constant Definitions
const int MAX_STR = 1024;

// Free Function Implementation
struct Metadata *readMetadata( const char *filename, int ioTime, int processorTime )
{
    // Open given file, exit if doesnt exist
    FILE *metadataFile = fopen( filename, "r" );
    if( metadataFile == NULL )
    {
        fprintf( stderr, "Error: Unable to open metadata file.\n Check that the file exists and you have read permissions.\n" );
        exit( 1 );
    }

    // Create Parent and child node for linked list
    struct Metadata *metadataHead = NULL;

    char line[MAX_STR];
    int lineCount = 0;


    while( 1 )
    {

        fgets( line, MAX_STR, metadataFile );

        if( stringCompare( line, "\n" ) == 0 )
        {
            break;
        }

        if( lineCount == 0 && stringCompare( line, "Start Program Meta-Data Code:\n" ) != 0 )
        {
            fprintf( stderr, "Error: No start statement" );
            exit( 1 );
        }

        if( stringCompare( line, "Start Program Meta-Data Code:\n" ) ==0 )
        {
          if( lineCount ==0 )
          {
              lineCount++;
              continue;
          }
          else
          {
              fprintf( stderr, "Error: Found start statement not on first line." );
              exit( 1 );
          }
        }

        else if( stringCompare( line, "End Program Meta-Data Code.\n" ) ==0 )
        {
            break;
        }

        else
        {
            char left[MAX_STR];
            char right[MAX_STR];
            struct Metadata *currentNode;

            while( 1 )
            {
                stringTokenLeft( line, left, ';' );
                currentNode = createMetadataNode( left );

                stringTokenRight( line, line, ';' );
                stringTokenRight( left, right, '.' );

                if( ( currentNode->letter != 'A' &&
                    currentNode->letter != 'I' &&
                    currentNode->letter != 'M' &&
                    currentNode->letter != 'O' &&
                    currentNode->letter != 'P' &&
                    currentNode->letter != 'S' ) ||
                    ( stringCompare( currentNode->command, "access" ) != 0 &&
                    stringCompare( currentNode->command, "allocate" ) != 0 &&
                    stringCompare( currentNode->command, "end" ) != 0 &&
                    stringCompare( currentNode->command, "hard drive" ) != 0 &&
                    stringCompare( currentNode->command, "keyboard" ) != 0 &&
                    stringCompare( currentNode->command, "monitor" ) != 0 &&
                    stringCompare( currentNode->command, "printer" ) != 0 &&
                    stringCompare( currentNode->command, "run" ) != 0 &&
                    stringCompare( currentNode->command, "start" ) != 0 )  )
                    {
                        fprintf( stderr, "Error: Found incorrect value in metadata file.\n");
                        exit( 1 );
                    }

                    switch( currentNode->letter )
                    {
                        case( 'A' ):
                            currentNode->time = 0;
                            break;

                        case( 'I' ):
                            currentNode->time = 0;
                            break;

                        case( 'M' ):
                            currentNode->time = 100;
                            break;

                        case( 'O' ):
                            currentNode->time = ioTime;
                            break;

                        case( 'P' ):
                            currentNode->time = ioTime;
                            break;

                        case( 'S' ):
                            currentNode->time = processorTime;
                            break;
                    }

                if( metadataHead == NULL)
                {
                    fprintf(stderr, "%s\n", "first");
                    metadataHead = currentNode;
                }
                else
                {
                    pushMetadataNode( metadataHead, currentNode );
                }

                if( stringCompare( line, "" ) == 0 || stringCompare( right, "" ) == 0 )
                {
                    break;
                }
            }
        lineCount++;
        }

    }

    fclose(metadataFile);
    printMetadata( metadataHead );
    return metadataHead;
}

// Free Function Implementation
struct Metadata *createMetadataNode( char *string )
{
    struct Metadata *metadataNode = malloc( sizeof( struct Metadata )  );
    metadataNode->command = malloc( MAX_STR );

    int count = 0;
    int iter = 0;

    while( string[count] != '(' )
    {
        count++;
    }
    metadataNode->letter = string[count - 1];

    count++;
    while( string[count] != ')' )
    {
        metadataNode->command[iter] = string[count];
        iter++;
        count++;
    }

    count++;
    iter = 0;
    char numString[MAX_STR];
    while( string[count] != '\0' && string[count] != '.')
    {
        numString[iter++] = string[count++];
    }
    numString[iter] = '\0';
    metadataNode->number = stringToInteger( numString );

    metadataNode->nextNode = NULL;

    return metadataNode;
}


void pushMetadataNode( struct Metadata *head, struct Metadata *node )
{
    struct Metadata *current = head;
    while( current->nextNode != NULL )
    {
        current = current->nextNode;
    }
    current->nextNode = node;
}

// Free Function Implementation
void printMetadata( struct Metadata *head )
{
    struct Metadata *current = head;

    while( current != NULL )
    {
        fprintf( stderr, "Node -------------\n" );
        fprintf( stderr, "letter: %c\n", current->letter );
        fprintf( stderr, "command: %s\n", current->command );
        fprintf( stderr, "number: %d\n", current->number );
        current = current->nextNode;
    }
}

// Free Function Implementation
void deleteMetadata( struct Metadata *head )
{
    struct Metadata *current = head;
    struct Metadata *nextNode;

    while( current != NULL )
    {
        nextNode = current->nextNode;
        free(current->command);
        free(current);
        current = nextNode;
    }
}

// Precompiler
#endif
