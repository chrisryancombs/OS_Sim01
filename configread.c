#include "configread.h"

#define VERSION 1
#define FILEPATH 2
#define CPU_CODE 3
#define QUANTUM_TIME 4
#define MEM_AVAILABLE 5
#define PROC_TIME 6
#define IO_TIME 7
#define LOG_TO 8
#define LOG_PATH 9

const int MAX_STR = 1024;

struct config read_config(const char *filename)
{


  char line[MAX_STR];
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
      fgets(line, MAX_STR, configfile);
      if(line_count==0  && strcmp(line, "Start Simulator Configuration File\n")==0)
      {
        line_count++;
        fprintf(stderr, "found start\n");
        continue;
      }
      else if(strcmp(line, "End Simulator Configuration File.\n")==0)
      {
        line_count++;
        fprintf(stderr, "found end\n");
        break;
      }
      else
      {
        line_count++;
        key = strtok(line, ":");
        val = strtok(NULL, " ");
        switch(get_keynum(key))
        {
          case VERSION :
            config_values.version = atoi(val);
            break;

          case FILEPATH :
            config_values.filepath = val;
            break;

          case CPU_CODE :
            if (strcmp(val, "NONE") == 0)
            {
              val = "FCFS-N";
            }
            config_values.cpu_scheduling_code = val;
            break;

          case QUANTUM_TIME :
            config_values.quantum_time = atoi(val);
            break;

          case MEM_AVAILABLE :
            config_values.memory_available = atoi(val);
            break;

          case PROC_TIME :
            config_values.processor_time = atoi(val);
            break;

          case IO_TIME :
            config_values.io_time = atoi(val);
            break;

          case LOG_TO :
            config_values.log_to = val;
            break;

          case LOG_PATH :
            config_values.log_filepath = val;
            break;
        }
      }
    }
  }

  return config_values;
}


// Helper function to get a int value for out current key. This allows for a
// clean switch statement in the read_config function.
int get_keynum(char *key)
{
  if(strcmp(key, "Version/Phase") == 0)
  {
    return VERSION;
  }
  else if (strcmp(key, "File Path") == 0)
  {
    return FILEPATH;
  }
  else if (strcmp(key, "CPU Scheduling Code") == 0)
  {
    return CPU_CODE;
  }
  else if (strcmp(key, "Quantum Time (cycles)") == 0)
  {
    return QUANTUM_TIME;
  }
  else if (strcmp(key, "Memory Available (KB)") == 0)
  {
    return MEM_AVAILABLE;
  }
  else if (strcmp(key, "Processor Cycle Time (msec)") == 0)
  {
    return PROC_TIME;
  }
  else if (strcmp(key, "I/O Cycle Time (msec)") == 0)
  {
    return IO_TIME;
  }
  else if (strcmp(key, "Log To") == 0)
  {
    return LOG_TO;
  }
  else if (strcmp(key, "Log File Path") == 0)
  {
    return LOG_PATH;
  }
  else
    return 0;
}
