#include "configread.h"

const int MAX_LINE = 1024;

struct config read_config(const char *filename)
{
  char line[MAX_LINE];
  int line_count = 0;
  char *key;
  char *val;
  struct config config_values;

  FILE *configfile = fopen(filename, "r");
  if (configfile == NULL)
  {
    fprintf(stderr, "Error: Unable to open config file.\n" );
  }
  else
  {
    while(1)
    {
      fgets(line, MAX_LINE, configfile);
      if(line_count==0  && strcmp(line, "Start Simulator Configuration File\n")==0)
      {
        line_count++;
        continue;
      }
      else if(strcmp(line, "End Simulator Configuration File.\n")==0)
      {
        break;
      }
      else
      {
        line_count++;
        key = strtok(line, ":");
        val = strtok(NULL, " ");

        if(strcmp(key, "Version/Phase") == 0)
        {
          config_values.version = atoi(val);
        }
        else if (strcmp(key, "File Path") == 0)
        {
          config_values.filepath = val;
        }
        else if (strcmp(key, "CPU Scheduling Code") == 0)
        {
          if (strcmp(val, "NONE") == 0)
          {
            val = "FCFS-N";
          }
          config_values.cpu_scheduling_code = val;
        }
        else if (strcmp(key, "Quantum Time (cycles)") == 0)
        {
          config_values.quantum_time = atoi(val);
        }
        else if (strcmp(key, "Memory Available (KB)") == 0)
        {
          config_values.memory_available = atoi(val);
        }
        else if (strcmp(key, "Processor Cycle Time (msec)") == 0)
        {
          config_values.processor_time = atoi(val);
        }
        else if (strcmp(key, "I/O Cycle Time (msec)") == 0)
        {
          config_values.io_time = atoi(val);
        }
        else if (strcmp(key, "Log To") == 0)
        {
          config_values.log_to = val;
        }
        else if (strcmp(key, "Log File Path") == 0)
        {
          config_values.log_filepath = val;
        }
      }
    }
  }

  return config_values;
}
