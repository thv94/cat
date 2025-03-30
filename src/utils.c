#include "utils.h"

bool_t is_directory(const char* path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) == -1)
    {
        return b_false;
    }

    return S_ISDIR(statbuf.st_mode);
}
