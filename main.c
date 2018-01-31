#include "configread.h"
#include "metaread.h"

int main(int argc, char const *argv[])
{
  read_config(argv[1]);
  struct metadata *md = read_metadata(argv[2]);
  md = md->nextnode;
  // fprintf(stderr, "First Node\n");
  // fprintf(stderr, "letter: %c\n", md->letter);
  // fprintf(stderr, "command: %s\n", md->command);
  // fprintf(stderr, "number: %d\n", md->number);
}
