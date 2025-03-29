#include <stdio.h>
#include <stdlib.h>
#include "types.h"

#define KB        1024
#define NUM_KB    8
#define BUFSIZE   (NUM_KB * KB)

void multi_cat(int argc, char **argv);
void simple_cat(char* filename);

int main(int argc, char **argv)
{
    switch(argc)
    {
        case 1:
            /* Read from stdin */
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

void simple_cat(char* filename)
{
    u8 buffer[BUFSIZE];
    size_t bytes_read;
    FILE *input_file;

    input_file = fopen(filename, "r");

    if (NULL != input_file)
    {
        while ((bytes_read = fread(buffer, sizeof(u8), sizeof(buffer), input_file)) > 0)
        {
            fwrite(buffer, sizeof(u8), bytes_read, stdout);
        }

        fclose(input_file);
    }
    else 
    {
        perror("Error opening file");
    }
}

void multi_cat(int argc, char **argv)
{
    s32 i;

    for (i = 1; i < argc; i++)
    {
        simple_cat(argv[i]);
    }
}
