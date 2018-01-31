#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct metadata *read_metadata(const char *filename);
void string_token_left(char *string, char *substring, char delim);
void string_token_right(char *string, char *substring, char delim);
struct metadata *create_metadata_node(char *string);


struct metadata
{
  char letter;
  char *command;
  int number;
  struct metadata *nextnode;

};
