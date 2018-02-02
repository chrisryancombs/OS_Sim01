#include "configread.h"
#include "metaread.h"

int main(int argc, char const *argv[])
{
  struct config config_values = read_config(argv[1]);
  struct metadata *md = read_metadata(config_values.filepath);

}
