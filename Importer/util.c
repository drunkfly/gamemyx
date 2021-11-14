/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"
#include <errno.h>

#ifdef _WIN32
#include <dirent.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

void createDirectories(const char* file)
{
    const char* fileEnd = strrchr(file, '/');
    const char* fileEnd2 = strrchr(file, '\\');
    if (fileEnd2 && (!fileEnd || fileEnd < fileEnd2))
        fileEnd = fileEnd2;

    if (!fileEnd)
        return;

    char path[1024];
    memcpy(path, file, fileEnd - file);
    path[fileEnd - file] = 0;

  #ifdef _WIN32
    int r = mkdir(path);
  #else
    int r = mkdir(path, 0755);
  #endif
    if (r < 0 && errno != EEXIST) {
        fprintf(stderr, "error: mkdir(%s) failed: %s\n", path, strerror(errno));
        exit(1);
    }
}
