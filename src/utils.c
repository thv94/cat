#include "utils.h"

bool is_directory(const char* path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) == -1)
    {
        return false;
    }

    return S_ISDIR(statbuf.st_mode);
}
