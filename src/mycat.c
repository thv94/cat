#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define KB        1024
#define NUM_KB    8
#define BUFSIZE   (NUM_KB * KB)
#define LINE_NUM_BUFF_SIZE 20
#define STARTING_LINE_NUMBER 1

void stdin_cat(void);
int simple_cat(const char* filename, int line_number);
void multi_cat(int argc, char **argv);

int main(int argc, char **argv)
{
    switch(argc)
    {
        case 1:
            stdin_cat();
            break;
        case 2:
            simple_cat(argv[1], STARTING_LINE_NUMBER);
            break;
        default:
            multi_cat(argc, argv);
            break;
    }

    return EXIT_SUCCESS;
}

void stdin_cat(void)
{
    char buffer[BUFSIZE];
    char line_num_str[LINE_NUM_BUFF_SIZE];
    int line_number = STARTING_LINE_NUMBER;

    while (NULL != fgets(buffer, sizeof(buffer), stdin))
    {
        sprintf(line_num_str, "%6d   ", line_number);
        line_number++;
        fputs(line_num_str, stdout);
        fputs(buffer, stdout);
    }
}

int simple_cat(const char* filename, int start_line_index)
{
    char buffer[BUFSIZE];
    size_t bytes_read;
    size_t i;
    FILE *input_file;
    char line_num_str[LINE_NUM_BUFF_SIZE];
    int line_number = start_line_index;
    long file_size;

    if (is_directory(filename))
    {
        fprintf(stderr, "%s is a directory.\n", filename);
        return STARTING_LINE_NUMBER;
    }
    
    input_file = fopen(filename, "r");

    if (NULL == input_file)
    {
        fprintf(stderr, "Error opening file %s: ", filename);
        perror(NULL);
        return STARTING_LINE_NUMBER;
    }

    /* Check for empty file */
    fseek(input_file, 0, SEEK_END);
    file_size = ftell(input_file);
    rewind(input_file);
   
    if (file_size > 0)
    {
        sprintf(line_num_str, "%6d   ", line_number);
        fwrite(line_num_str, 1, strlen(line_num_str), stdout);
        line_number++;
            
        while ((bytes_read = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input_file)) > 0)
        {
            for (i = 0; i < bytes_read; i++)
            {
                /* End of buffer will be 0's not EOF like reading a file (WILL IT?)*/
                if ((buffer[i] == '\n') && (buffer[i+1] != 0))
                {
                    fwrite(&buffer[i], 1, 1, stdout);
                    sprintf(line_num_str, "%6d   ", line_number);
                    fwrite(line_num_str, 1, strlen(line_num_str), stdout);
                    line_number++;
                }
                else
                {
                    fwrite(&buffer[i], 1, 1, stdout);
                }
            }
        }
    }

    fclose(input_file);

    return line_number;
}

void multi_cat(int argc, char **argv)
{
    int i;
    int line_number = STARTING_LINE_NUMBER;

    for (i = 1; i < argc; i++)
    {
        line_number = simple_cat(argv[i], line_number);
    }
}
