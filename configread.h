#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"


struct config read_config(const char *filename);
void print_config(struct config config_values);


struct config
{
  int version;
  char *filepath;
  char *cpu_scheduling_code;
  int quantum_time;
  int memory_available;
  int processor_time;
  int io_time;
  char *log_to;
  char *log_filepath;
};
