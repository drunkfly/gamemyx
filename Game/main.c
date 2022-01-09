/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include "character.h"
#include "data/data.h"
#include "level.h"

void GameMain()
{
    /* load common data: sprites, palettes, etc. into memory */
    GAME_LoadData();

    /* load first game level */
    GAME_LoadLevel(&map_New_Year_Home_tmx);
    MYX_LoadTileset(InsideTileset, INSIDETILESET_BANK);

    for (;;) {
        GAME_RunLevel();
    }
}
