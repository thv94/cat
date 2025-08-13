#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "utils.h"

typedef enum
{
    FALSE,
    TRUE
} BOOL_T;

#define KB        1024
#define NUM_KB    8
#define BUFSIZE   (NUM_KB * KB)
#define LINE_NUM_BUFF_SIZE 20
#define DEFAULT_STARTING_LINE_NUMBER 1
#define LINE_NUMBER_FORMAT_STR "%6d   "

void stdin_cat(BOOL_T enable_line_numbers);
void simple_cat(const char* filename, BOOL_T enable_line_number);
void multi_cat(int argc, char **argv);

int main(int argc, char **argv)
{
    int opt;
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
                fprintf(stderr, "Unknown option: -%c\n", optopt);
                return EXIT_FAILURE;
        }
    }

    if (optind == argc)
    {
        stdin_cat(enable_line_numbers);
    }
    else
    {
        /* Process remaining file names */
        for (; optind < argc; optind++)
        {
            simple_cat(argv[optind], enable_line_numbers);
        }
    }

    return EXIT_SUCCESS;
}

void stdin_cat(BOOL_T enable_line_numbers)
{
    char buffer[BUFSIZE];
    char line_num_str[LINE_NUM_BUFF_SIZE];
    int line_number = DEFAULT_STARTING_LINE_NUMBER;

    while (NULL != fgets(buffer, sizeof(buffer), stdin))
    {
        if(enable_line_numbers)
        {
            sprintf(line_num_str, LINE_NUMBER_FORMAT_STR, line_number);
            line_number++;
            fputs(line_num_str, stdout);
        }

        fputs(buffer, stdout);
    }
}

void simple_cat(const char* filename, BOOL_T enable_line_numbers)
{
    char buffer[BUFSIZE];
    size_t bytes_read;
    size_t read_buffer_idx;
    FILE *input_file;
    char line_num_str[LINE_NUM_BUFF_SIZE];
    static int line_number = DEFAULT_STARTING_LINE_NUMBER;
    long file_size;

    if (is_directory(filename))
    {
        fprintf(stderr, "%s is a directory.\n", filename);
    }
    
    input_file = fopen(filename, "r");

    if (NULL == input_file)
    {
        fprintf(stderr, "Error opening file %s: ", filename);
        perror(NULL);
    }

    /* Check for empty file */
    fseek(input_file, 0, SEEK_END);
    file_size = ftell(input_file);
    rewind(input_file);
   
    if (file_size > 0)
    {
        if (enable_line_numbers)
        {
            sprintf(line_num_str, LINE_NUMBER_FORMAT_STR, line_number);
            fwrite(line_num_str, 1, strlen(line_num_str), stdout);
            line_number++;
        }
            
        while ((bytes_read = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input_file)) > 0)
        {
            for (read_buffer_idx = 0; read_buffer_idx< bytes_read; read_buffer_idx++)
            {
                if (enable_line_numbers)
                {
                    /* End of buffer will be 0's not EOF like reading a file */
                    if ((buffer[read_buffer_idx] == '\n') && (buffer[read_buffer_idx+1] != 0))
                    {
                        fwrite(&buffer[read_buffer_idx], 1, 1, stdout);
                        sprintf(line_num_str, LINE_NUMBER_FORMAT_STR, line_number);
                        fwrite(line_num_str, 1, strlen(line_num_str), stdout);
                        line_number++;
                    }
                    else
                    {
                        fwrite(&buffer[read_buffer_idx], 1, 1, stdout);
                    }
                }
                else
                {
                    fwrite(&buffer[read_buffer_idx], 1, 1, stdout);
                }
            }
        }
    }

    fclose(input_file);
}
