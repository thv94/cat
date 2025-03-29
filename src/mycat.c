#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024

typedef enum 
{  
   true,
   false
} BOOL_T;

void cat(FILE *input_file);
BOOL_T validate_args(int argc, char **argv);

int main(int argc, char **argv)
{
    int result;
    BOOL_T args_valid;
    FILE *input_file;

    args_valid = validate_args(argc, argv);

    if (true == args_valid)
    {
        input_file = fopen(argv[1], "r");

        if (NULL != input_file)
        {
            cat(input_file);
            fclose(input_file);
            result = EXIT_SUCCESS;
        }
        else 
        {
            printf("Error opening %s\n", argv[1]);
            result = EXIT_FAILURE;
        }
    }
    else 
    {
        printf("Usage: mycat <filename>\n");
        result = EXIT_FAILURE;
    }
 
    return result;
}

BOOL_T validate_args(int argc, char **argv)
{
    BOOL_T args_valid;
    
    (void)argv; /* currently not used for validation */

    args_valid = true;

    if (2 != argc)
    {
        args_valid = false;
    }

    return args_valid;
}

void cat(FILE *input_file)
{
    char buffer[BUFSIZE];
    size_t bytes_read;

    bytes_read = fread(buffer, sizeof(char), sizeof(buffer), input_file);
 
    while (bytes_read > 0)
    {
        fwrite(buffer, sizeof(char), bytes_read, stdout);
        bytes_read = fread(buffer, sizeof(char), sizeof(buffer), input_file);
    }
}
