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
    struct metadata *meta_head = (struct metadata *)malloc(sizeof(struct metadata));
    meta_head->command = malloc(MAX_STR);
    meta_head->nextnode = NULL;

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
            struct metadata *current_node;

            while(1)
            {
                string_token_left(line, left, ';');
                current_node = create_metadata_node(left);
                printf("%s\n", "1");

                string_token_right(line, line, ';');
                string_token_right(left, right, '.');
                printf("%s\n", "2");

                if ((current_node->letter != 'A' &&
                    current_node->letter != 'I' &&
                    current_node->letter != 'M' &&
                    current_node->letter != 'O' &&
                    current_node->letter != 'P' &&
                    current_node->letter != 'S') ||
                    (strcmp(current_node->command, "access") != 0 &&
                    strcmp(current_node->command, "allocate") != 0 &&
                    strcmp(current_node->command, "end") != 0 &&
                    strcmp(current_node->command, "hard drive") != 0 &&
                    strcmp(current_node->command, "keyboard") != 0 &&
                    strcmp(current_node->command, "printer") != 0 &&
                    strcmp(current_node->command, "run") != 0 &&
                    strcmp(current_node->command, "start") != 0))
                    {
                        fprintf(stderr, "Error: Found incorrect value in metadata file.\n");
                        exit(1);
                    }

                    printf("%s\n", "3");

                push_metadata_node(meta_head, current_node);

                printf("%s\n", "7");

                if (strcmp(line, "") == 0 || strcmp(right, "") == 0)
                {
                    break;
                }

            }


        line_count++;
        }

    }
    meta_head = meta_head->nextnode;
    print_metadata(meta_head);

    return meta_head;
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
    meta_node->command = malloc(MAX_STR);
    while (string[command_count] != ')')
    {
        meta_node->command[command_iter++] = string[command_count++];
    }

    int number_count = command_count + 1;
    int number_iter = 0;
    char numstring[MAX_STR];
    while(string[number_count] != '\0')
    {
        numstring[number_iter++] = string[number_count++];
    }
    numstring[number_iter] = '\0';
    meta_node->number = atoi(numstring);

    meta_node->nextnode = NULL;

    return meta_node;
}

void push_metadata_node(struct metadata *head, struct metadata *node)
{

    struct metadata *current = head;
    while (current->nextnode != NULL)
    {
        current = current->nextnode;
    }
    current->nextnode = node;
}

void print_metadata(struct metadata *head)
{
    struct metadata *current = head;
    while(current->nextnode != NULL)
    {
        fprintf(stderr, "Node -------------\n");
        fprintf(stderr, "letter: %c\n", current->letter);
        fprintf(stderr, "command: %s\n", current->command);
        fprintf(stderr, "number: %d\n", current->number);
        current = current->nextnode;
    }


}
