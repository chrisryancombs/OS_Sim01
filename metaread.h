#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

struct metadata *read_metadata(const char *filename);
struct metadata *create_metadata_node(char *string);
void push_metadata_node(struct metadata *head, struct metadata *node);
void print_metadata(struct metadata *head);




struct metadata
{
  char letter;
  char *command;
  int number;
  struct metadata *nextnode;

};
