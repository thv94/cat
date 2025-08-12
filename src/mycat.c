#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define KB        1024
#define NUM_KB    8
#define BUFSIZE   (NUM_KB * KB)
#define LINE_NUM_BUFF_SIZE 20

void stdin_cat(void);
void simple_cat(const char* filename);
void multi_cat(int argc, char **argv);

int main(int argc, char **argv)
{
    switch(argc)
    {
        case 1:
            stdin_cat();
            break;
        case 2:
            simple_cat(argv[1]);
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

    while (NULL != fgets(buffer, sizeof(buffer), stdin))
    {
        fputs(buffer, stdout);
    }
}

void simple_cat(const char* filename)
{
    char buffer[BUFSIZE];
    size_t bytes_read;
    size_t i;
    FILE *input_file;
    char line_num_str[LINE_NUM_BUFF_SIZE];
    int line_number = 1;

    if (is_directory(filename))
    {
        fprintf(stderr, "%s is a directory.\n", filename);
        return;
    }
    
    input_file = fopen(filename, "r");

    if (NULL == input_file)
    {
        fprintf(stderr, "Error opening file %s: ", filename);
        perror(NULL);
        return;
    }
   
    /* This assumes we have a first line, probably need a check here
       that the file is not empty */
    sprintf(line_num_str, "%6d   ", line_number);
    fwrite(line_num_str, 1, strlen(line_num_str), stdout);
    line_number++;
        
    while ((bytes_read = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input_file)) > 0)
    {
        for (i = 0; i < bytes_read; i++)
        {
            /* End of buffer will be 0's not EOF like reading a file */
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

    fclose(input_file);
}

void multi_cat(int argc, char **argv)
{
    int i;

    for (i = 1; i < argc; i++)
    {
        simple_cat(argv[i]);
    }
}
