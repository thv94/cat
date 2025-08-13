#include "utils.h"

BOOL_T is_directory(const char* path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) == -1)
    {
        return FALSE;
    }

    return S_ISDIR(statbuf.st_mode);
}
