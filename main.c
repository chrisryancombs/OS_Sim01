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

#include "configread.h"
#include "metaread.h"

int main(int argc, char const *argv[])
{
  struct config config_values = read_config(argv[1]);
  struct metadata *md = read_metadata(config_values.filepath);

}
