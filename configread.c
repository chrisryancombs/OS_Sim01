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
  char *key = "";

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
        key = strtok(line, ":");
        switch(get_keynum(key))
        {
          case VERSION :
            fprintf(stderr, "doo\n");
          case FILEPATH :
            fprintf(stderr, "yo\n");
          case CPU_CODE :
            fprintf(stderr, "cpu\n");
          case QUANTUM_TIME :
            fprintf(stderr, "q\n");
          case MEM_AVAILABLE :
            fprintf(stderr, "mem\n");
          case PROC_TIME :
            fprintf(stderr, "pr\n");
          case IO_TIME :
            fprintf(stderr, "io\n");
          case LOG_TO :
            fprintf(stderr, "to\n");
          case LOG_PATH :
            fprintf(stderr, "path\n");
        }
      }
    }
  }
}

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
}
