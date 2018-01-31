#include "metaread.h"

const int MAX_STR = 1024;

struct metadata *read_metadata(const char *filename)
{
    // Open given file, exit if doesnt exist
    FILE *metadata_file = fopen(filename, "r");
    if (metadata_file == NULL)
    {
        fprintf(stderr, "Error: Unable to open metadata file.\n Check that the file exists and you have read permissions.\n" );
        exit(1);
    }

    // Create Parent and child node for linked list
    struct metadata *meta_head = malloc(sizeof(struct metadata));;
    struct metadata *meta_node = malloc(sizeof(struct metadata));
    meta_node->command = malloc(MAX_STR);
    meta_head = meta_node;

    char line[MAX_STR];
    int line_count = 0;


    while(1)
    {

        fgets(line, MAX_STR, metadata_file);

        if(strcmp(line, "\n") == 0)
        {
            break;
        }

        if(line_count == 0 && strcmp(line, "Start Program Meta-Data Code:\n") != 0)
        {
            fprintf(stderr, "Error: No start statement");
            exit(1);
        }
        else
        {

        }

        if(strcmp(line, "Start Program Meta-Data Code:\n")==0)
        {
          if (line_count ==0)
          {
              line_count++;
              continue;
          }
          else
          {
              fprintf(stderr, "Error: Found start statement not on first line.");
              exit(1);
          }
        }

        else if(strcmp(line, "End Program Meta-Data Code.\n")==0)
        {
            break;
        }

        else
        {
            char left[MAX_STR];
            char right[MAX_STR];

            while(1)
            {
                if (strcmp(line, "") == 0)
                {
                    fprintf(stderr, "end\n" );
                    break;
                }

                string_token_left(line, left, ';');
                fprintf(stderr, "left: %s\n", left );
                string_token_right(line, line, ';');
                fprintf(stderr, "line: %s\n", line);

                meta_node = create_metadata_node(left);

                if ((meta_node->letter != 'A' &&
                    meta_node->letter != 'I' &&
                    meta_node->letter != 'M' &&
                    meta_node->letter != 'O' &&
                    meta_node->letter != 'P' &&
                    meta_node->letter != 'S') ||
                    (strcmp(meta_node->command, "access") != 0 &&
                    strcmp(meta_node->command, "allocate") != 0 &&
                    strcmp(meta_node->command, "end") != 0 &&
                    strcmp(meta_node->command, "hard drive") != 0 &&
                    strcmp(meta_node->command, "keyboard") != 0 &&
                    strcmp(meta_node->command, "printer") != 0 &&
                    strcmp(meta_node->command, "run") != 0 &&
                    strcmp(meta_node->command, "start") != 0))
                    {
                        fprintf(stderr, "Error: Found incorrect value iin metadata file.\n");
                        exit(1);
                    }

            }


        line_count++;
        }

    }

    return meta_head;
}

void string_token_left(char *string, char* substring, char delim)
{
    int count = 0;
    while (string[count] != delim){
        substring[count] = string[count];
        count++;
    }
    substring[count] = '\0';
}

void string_token_right(char *string, char* substring, char delim)
{
    int count = 0;
    while (string[count] != delim)
    {
        count++;
    }
    count++;

    while (string[count] == ' ')
    {
        count++;
    }
    int end_count = count;
    while(string[end_count] != '\n'){
        end_count++;
    }

    int iter = count;
    while (iter < end_count)
    {
        substring[iter - count] = string[iter];
        iter++;
    }
    substring[iter - count] = '\0';
}

struct metadata *create_metadata_node(char *string)
{
    struct metadata *meta_node = malloc(sizeof(struct metadata));
    meta_node->command = malloc(MAX_STR);

    int letter_count = 0;
    while (string[letter_count] != '(')
    {
        letter_count++;
    }
    meta_node->letter = string[letter_count - 1];

    int command_count = letter_count + 1;
    int command_iter = 0;
    while (string[command_count] != ')')
    {
        meta_node->command[command_iter++] = string[command_count++];
    }

    int number_count = command_count + 1;
    int number_iter = 0;
    char *numstring[MAX_STR];
    while(string[number_count] != '\0')
    {
        numstring[number_iter++] = string[number_count++];
    }
    meta_node->number = atoi(numstring);

    return meta_node;
}
