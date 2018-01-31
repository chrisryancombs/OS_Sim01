#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct metadata *read_metadata(const char *filename);

struct metadata
{
  char letter;
  char *command;
  int number;
  struct metadata *nextnode;

};
