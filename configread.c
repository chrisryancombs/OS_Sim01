// Code Implementation File Information /////////////////////////////
/**
* @file configread.c
*
* @brief Implementation file for configread code
*
* @details Implements all functions of the configread utilities
*
*
* @version 1.00
* C.S. Student ( 2 February 2018 )
* Initial development and testing of configread code
*
* @note Requires configread.h
*/

// Header Files ///////////////////////////////////////////////////
//
    #include "configread.h"
//
// Global Constant Definitions ////////////////////////////////////
//
    const int MAX_LINE = 1024;
//
// Free Function Implementation ///////////////////////////////////
//
/**
* @brief readConfig Parses a config file for keys and values
*
* @details Reads in a config file and stores each of the values found
* in their correspinding variables in a Config struct.
*
* @pre const char *filename contains a config filename
*
* @post struct Config contains all values parsed for in config file
*
*/
    struct Config readConfig( const char *filename )
    {
        char line[MAX_LINE];
        int lineCount = 0;
        char key[MAX_LINE];
        char val[MAX_LINE];
        struct Config configValues;

        FILE *configFile = fopen( filename, "r" );
        if( configFile == NULL )
        {
            fprintf( stderr, "Error: Unable to open config file.\n"  );
            exit(1);
        }
        else
        {
            while( 1 )
            {
                fgets( line, MAX_LINE, configFile );
                if( lineCount == 0  && stringCompare(
                            line, "Start Simulator Configuration File\n" ) == 0 )
                {
                    lineCount++;
                    continue;
                }
                else if( stringCompare(
                        line, "End Simulator Configuration File.\n" ) == 0 )
                {
                    break;
                }
                else
                {
                    lineCount++;
                    stringTokenLeft( line, key, ':' );
                    stringTokenRight( line, val, ':' );
                    if( stringCompare( key, "Version/Phase" ) == 0 )
                    {
                        configValues.version = stringToInteger( val );
                    }
                    else if ( stringCompare( key, "File Path" ) == 0 )
                    {
                        configValues.filepath = malloc( MAX_LINE );
                        stringCopy( configValues.filepath, val );
                    }
                    else if ( stringCompare( key, "CPU Scheduling Code" ) == 0 )
                    {
                        configValues.cpuSchedulingCode = malloc( MAX_LINE );
                        if ( stringCompare( val, "NONE" ) == 0 )
                        {
                            stringCopy( val,"FCFS-N" );
                        }
                        stringCopy( configValues.cpuSchedulingCode, val );
                    }
                    else if ( stringCompare( key, "Quantum Time (cycles)" ) == 0 )
                    {
                        configValues.quantumTime = stringToInteger( val );
                    }
                    else if ( stringCompare( key, "Memory Available (KB)" ) == 0 )
                    {
                        configValues.memoryAvailable = stringToInteger( val );
                    }
                    else if ( stringCompare( key, "Processor Cycle Time (msec)" ) == 0 )
                    {
                        configValues.processorTime = stringToInteger( val );
                    }
                    else if ( stringCompare( key, "I/O Cycle Time (msec)" ) == 0 )
                    {
                        configValues.ioTime = stringToInteger( val );
                    }
                    else if ( stringCompare( key, "Log To" ) == 0 )
                    {
                        configValues.logTo = malloc( MAX_LINE );
                        stringCopy( configValues.logTo, val );
                    }
                    else if ( stringCompare( key, "Log File Path" ) == 0 )
                    {
                        configValues.logFilepath = malloc( MAX_LINE );
                        stringCopy( configValues.logFilepath, val );
                    }
                    else
                    {
                        printf("Error: Found incorrect value in config file: %s\n", line);
                        exit( 1 );
                    }
                }
            }
        }

        fclose(configFile);
        // printConfig( configValues );
        return configValues;
    }

//
// Free Function Implementation ///////////////////////////////////
//
    void printConfig( struct Config configValues )
    {
        printf( "Config -------------\n" );
        printf( "Version/Path:                 %d\n", configValues.version );
        printf( "File Path:                    %s\n", configValues.filepath );
        printf( "CPU Scheduling Code:          %s\n", configValues.cpuSchedulingCode );
        printf( "Quantum Time ( cycles ):        %d\n", configValues.quantumTime );
        printf( "Memory Available ( KB ):        %d\n", configValues.memoryAvailable );
        printf( "Processor Cycle Time ( msec ):  %d\n", configValues.processorTime );
        printf( "I/O Cycle Time ( msec ):        %d\n", configValues.ioTime );
        printf( "Log To:                       %s\n", configValues.logTo );
        printf( "Log File Path:                %s\n", configValues.logFilepath );
    }

//
// Free Function Implementation ///////////////////////////////////
//
    void deleteConfig( struct Config configValues )
    {
        free(configValues.filepath);
        free(configValues.cpuSchedulingCode);
        free(configValues.logTo);
        free(configValues.logFilepath);
    }
