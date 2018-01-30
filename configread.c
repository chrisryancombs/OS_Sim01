#include "configread.h"


const int MAX_STR = 1024;

struct config read_config(const char *filename)
{


  char line[MAX_STR];
  int line_count = 0;

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
      if(line_count!=0 &&  strcmp(line, "End Simulator Configuration File.\n")==0)
      {
        line_count++;
        fprintf(stderr, "found end\n");
        break;
      }
    }
  }
}
