#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"

#define KB        1024
#define NUM_KB    8
#define BUFSIZE   (NUM_KB * KB)

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
    FILE *input_file;

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
        
    while ((bytes_read = fread(buffer, sizeof(buffer[0]), sizeof(buffer), input_file)) > 0)
    {
        fwrite(buffer, sizeof(buffer[0]), bytes_read, stdout);
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
