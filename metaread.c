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
    meta_head = meta_node;

    char line[MAX_STR];
    int line_count = 0;

    while(1)
    {
        fgets(line, MAX_STR, metadata_file);

        if(line_count == 0 && strcmp(line, "Start Program Meta-Data Code:\n") != 0)
        {
            fprintf(stderr, "Error: No start statement");
            exit(1);
        }

        if(strcmp(line, "Start Program Meta-Data Code:\n")==0)
        {
          if (line_count ==0)
          {
              line_count++;
          }
          else
          {
              fprintf(stderr, "Error: Found start statement not on first line.");
              exit(1);
          }
        }

        if(strcmp(line, "End Program Meta-Data Code.\n")==0)
        {
            break;
        }

        char extra = fgetc(metadata_file);
        while(extra == '\n' || extra == ' ')
        {
            fgetc(metadata_file);
        }
        ungetc(extra, metadata_file);

        while(1)
        {

            fscanf(metadata_file, "%c(%[^()])%i", &meta_node->letter, &meta_node->command, &meta_node->number);

            fprintf(stderr, &meta_node->letter);

            if (meta_node->letter != 'S' &&
                meta_node->letter != 'A' &&
                meta_node->letter != 'M' &&
                meta_node->letter != 'I' &&
                meta_node->letter != 'O' &&
                meta_node->letter != 'P')
                {
                    fprintf(stderr, "Error: Found incorrect value in metadata file.\n");
                    exit(1);
                }

            if (strcmp(meta_node->command, "start") != 0)
                {
                    fprintf(stderr, "Error: Found incorrect value in metadata file.\n");
                    exit(1);
                }
            // fprintf(stderr, meta_node->command);
            break;
        }


        line_count++;
        break;
    }

    return meta_head;
}
