#include "configread.h"
#include "metaread.h"

int main(int argc, char const *argv[])
{
  read_config(argv[1]);
  read_metadata(argv[2]);
}
