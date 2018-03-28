// Header File Information /////////////////////////////////////
/**
* @file utilities.h
*
* @brief Header file for utilities code
*
* @details Specifies functions, constants, and other information
* related to the utilities code
*
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing of utilities code
*
* @note None
*/
// Program Description/Support /////////////////////////////////////
/*
 This program uses a small file (config1.cnf) to support user
 configuration. If the file is not found, the user will be notified
 and the program will exit.
*/

// Header Files ///////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

// Free Function Prototypes ///////////////////////////////////////
void stringTokenLeft(char *string, char *substring, char delim);
void stringTokenRight(char *string, char *substring, char delim);
void stringCopy(char *dest, char *from);
int stringCompare(char *str1, char *str2);
int stringToInteger(char *string);
