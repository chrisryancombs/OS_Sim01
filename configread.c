// Code Implementation File Information /////////////////////////////
/**
* @file configread.c
*
* @brief Implementation file for configread code
*
* @details Implements all functions of the configread utilities
*
*
* @version 1.00
* C.S. Student (2 February 2018)
* Initial development and testing of configread code
*
* @note Requires configread.h
*/

#include "configread.h"

const int MAX_LINE = 1024;

struct config read_config(const char *filename)
{
    char line[MAX_LINE];
    int line_count = 0;
    char key[MAX_LINE];
    char val[MAX_LINE];
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
            if(line_count==0  && string_compare(line, "Start Simulator Configuration File\n")==0)
            {
                line_count++;
                continue;
            }
            else if(string_compare(line, "End Simulator Configuration File.\n")==0)
            {
                break;
            }
            else
            {
                line_count++;
                string_token_left(line, key, ':');
                string_token_right(line, val, ':');
                if(string_compare(key, "Version/Phase") == 0)
                {
                    config_values.version = string_to_integer(val);
                }
                else if (string_compare(key, "File Path") == 0)
                {
                    config_values.filepath = malloc(MAX_LINE);
                    string_copy(config_values.filepath, val);
                }
                else if (string_compare(key, "CPU Scheduling Code") == 0)
                {
                    config_values.cpu_scheduling_code = malloc(MAX_LINE);
                    if (string_compare(val, "NONE") == 0)
                    {
                        string_copy(val,"FCFS-N");
                    }
                    string_copy(config_values.cpu_scheduling_code, val);
                }
                else if (string_compare(key, "Quantum Time (cycles)") == 0)
                {
                    config_values.quantum_time = string_to_integer(val);
                }
                else if (string_compare(key, "Memory Available (KB)") == 0)
                {
                    config_values.memory_available = string_to_integer(val);
                }
                else if (string_compare(key, "Processor Cycle Time (msec)") == 0)
                {
                    config_values.processor_time = string_to_integer(val);
                }
                else if (string_compare(key, "I/O Cycle Time (msec)") == 0)
                {
                    config_values.io_time = string_to_integer(val);
                }
                else if (string_compare(key, "Log To") == 0)
                {
                    config_values.log_to = malloc(MAX_LINE);
                    string_copy(config_values.log_to, val);
                }
                else if (string_compare(key, "Log File Path") == 0)
                {
                    config_values.log_filepath = malloc(MAX_LINE);
                    string_copy(config_values.log_filepath, val);
                }
            }
        }
    }

    print_config(config_values);
    return config_values;
}


void print_config(struct config config_values)
{
    printf("Config -------------\n");
    printf("Version/Path:                 %d\n", config_values.version);
    printf("File Path:                    %s\n", config_values.filepath);
    printf("CPU Scheduling Code:          %s\n", config_values.cpu_scheduling_code);
    printf("Quantum Time (cycles):        %d\n", config_values.quantum_time);
    printf("Memory Available (KB):        %d\n", config_values.memory_available);
    printf("Processor Cycle Time (msec):  %d\n", config_values.processor_time);
    printf("I/O Cycle Time (msec):        %d\n", config_values.io_time);
    printf("Log To:                       %s\n", config_values.log_to);
    printf("Log File Path:                %s\n", config_values.log_filepath);


}
