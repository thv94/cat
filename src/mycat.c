#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "utils.h"

void stdin_cat(BOOL_T enable_line_numbers);
void cat_stream(FILE* input_stream, BOOL_T enable_line_numbers);

int main(int argc, char **argv)
{
    int opt;
    FILE* input_file;
    BOOL_T enable_line_numbers = FALSE;

    while ((opt = getopt(argc, argv, "n")) != -1)
    {
        switch(opt)
        {
            case 'n':
                enable_line_numbers = TRUE;
                break;
            default:
            case '?':
                return EXIT_FAILURE;
        }
    }

    if (optind == argc)
    {
        cat_stream(stdin, enable_line_numbers);
    }
    else
    {
        /* Process remaining file names */
        for (; optind < argc; optind++)
        {
            if (is_directory(argv[optind]))
            {
                fprintf(stderr, "mycat: %s: Is a directory\n", argv[optind]);
                continue;
            }
    
            input_file = fopen(argv[optind], "r");

            if (NULL == input_file)
            {
                fprintf(stderr, "Error opening file %s: ", argv[optind]);
                perror(argv[optind]);
                continue;
            }

            cat_stream(input_file, enable_line_numbers);

            fclose(input_file);
        }
    }

    return EXIT_SUCCESS;
}

void cat_stream(FILE* input_stream, BOOL_T enable_line_numbers)
{
    char buffer[8192]; /* 8KB */
    static int line_number = 1;

    while (NULL != fgets(buffer, sizeof(buffer), input_stream))
    {
        if (enable_line_numbers)
        {
            fprintf(stdout, "%6d   ", line_number);
            line_number++;
        }
        fputs(buffer, stdout);
    }
}
