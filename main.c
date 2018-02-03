// Program Information ////////////////////////////////////////////////
/**
 * @file main.c
*
* @brief Driver program to exercise configread.c and metaread.c
*
* @details Allows for ingestion of Config and Metadata files
*
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing
*
* @note Requires configread.h, configread.c,
*                metaread.h, metaread.c,
*                utilities.h, utilities.c.
*/

// Header Files ///////////////////////////////////////////////////
//
    #include "configread.h"
    #include "metaread.h"

//
// Main Function Implementation ///////////////////////////////////
//
    int main( int argc, char const *argv[] )
    {
      if( argc != 2 )
      {
          fprintf( stderr, "Incorrect number of arguments: %d\n", argc );
          exit( 1 );
      }
      struct Config config_values = readConfig( argv[1] );
      struct Metadata *metadata_values = readMetadata( config_values.filepath );

    }
