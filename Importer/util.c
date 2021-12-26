/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"
#include <errno.h>

#ifdef _MSC_VER
#include <direct.h>
#elif defined(_WIN32)
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

bool decodeFunc(Func *func, const char* value)
{
    if (!strcmp(value, "none"))
        return *func = FUNC_NONE, true;
    else if (!strcmp(value, "player_start"))
        return *func = FUNC_PLAYERSTART, true;
    else if (!strcmp(value, "enemy1"))
        return *func = FUNC_ENEMY1, true;
    else if (!strcmp(value, "enemy2"))
        return *func = FUNC_ENEMY2, true;
    else if (!strcmp(value, "enemy3"))
        return *func = FUNC_ENEMY3, true;
    else if (!strcmp(value, "enemy4"))
        return *func = FUNC_ENEMY4, true;
    else if (!strcmp(value, "enemy5"))
        return *func = FUNC_ENEMY5, true;
    else if (!strcmp(value, "enemy6"))
        return *func = FUNC_ENEMY6, true;
    else if (!strcmp(value, "enemy7"))
        return *func = FUNC_ENEMY7, true;
    else if (!strcmp(value, "enemy8"))
        return *func = FUNC_ENEMY8, true;
    else if (!strcmp(value, "enemy9"))
        return *func = FUNC_ENEMY9, true;
    else if (!strcmp(value, "npc1"))
        return *func = FUNC_NPC1, true;
    else if (!strcmp(value, "npc2"))
        return *func = FUNC_NPC2, true;
    else if (!strcmp(value, "npc3"))
        return *func = FUNC_NPC3, true;
    else if (!strcmp(value, "npc4"))
        return *func = FUNC_NPC4, true;
    else if (!strcmp(value, "npc5"))
        return *func = FUNC_NPC5, true;
    else if (!strcmp(value, "npc6"))
        return *func = FUNC_NPC6, true;
    else if (!strcmp(value, "npc7"))
        return *func = FUNC_NPC7, true;
    else if (!strcmp(value, "npc8"))
        return *func = FUNC_NPC8, true;
    else if (!strcmp(value, "npc9"))
        return *func = FUNC_NPC9, true;
    else if (!strcmp(value, "item1"))
        return *func = FUNC_ITEM1, true;
    else if (!strcmp(value, "item2"))
        return *func = FUNC_ITEM2, true;
    else if (!strcmp(value, "item3"))
        return *func = FUNC_ITEM3, true;
    else if (!strcmp(value, "item4"))
        return *func = FUNC_ITEM4, true;
    else if (!strcmp(value, "item5"))
        return *func = FUNC_ITEM5, true;
    else if (!strcmp(value, "item6"))
        return *func = FUNC_ITEM6, true;
    else if (!strcmp(value, "item7"))
        return *func = FUNC_ITEM7, true;
    else if (!strcmp(value, "item8"))
        return *func = FUNC_ITEM8, true;
    else if (!strcmp(value, "item9"))
        return *func = FUNC_ITEM9, true;
    else
        return false;
}

bool decodeDir(Direction *dir, const char* value)
{
    if (!strcmp(value, "left"))
        return *dir = DIR_LEFT, true;
    else if (!strcmp(value, "right"))
        return *dir = DIR_RIGHT, true;
    else if (!strcmp(value, "up"))
        return *dir = DIR_UP, true;
    else if (!strcmp(value, "down"))
        return *dir = DIR_DOWN, true;
    else if (!strcmp(value, "up-left"))
        return *dir = DIR_UP_LEFT, true;
    else if (!strcmp(value, "up-right"))
        return *dir = DIR_UP_RIGHT, true;
    else if (!strcmp(value, "down-left"))
        return *dir = DIR_DOWN_LEFT, true;
    else if (!strcmp(value, "down-right"))
        return *dir = DIR_DOWN_RIGHT, true;
    else
        return false;
}

void decodeProperty(const char* file, Properties* props, const char* name, const char* value)
{
    if (!strcmp(name, "func")) {
        if (!decodeFunc(&props->func, value))
            fprintf(stderr, "warning: unknown func \"%s\" in \"%s\".\n", value, file);
    } else if (!strcmp(name, "dir")) {
        if (!decodeDir(&props->dir, value))
            fprintf(stderr, "warning: unknown dir \"%s\" in \"%s\".\n", value, file);
    } else
        fprintf(stderr, "warning: unknown propery \"%s\" in \"%s\".\n", name, file);
}
