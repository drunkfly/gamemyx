/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include "character.h"

enum
{
    TAG_PLAYER,
    TAG_ENEMY,
};

static const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
#include "Data/Palettes/SwordsmanDeathPalette.h"
#include "Data/Palettes/RedDemonPalette.h"
};

#include "swordsman.h"
#include "reddemon.h"

static const byte TilemapData[] = {
#include "Data/Map/Tilemap.h"
};

static const byte TilesetData[] = {
#include "Data/Map/Tileset.h"
};

static const byte MapInfo[] = {
#include "Data/Map/Info.h"
};

static MYXSprite RedDemonIdleFrontSprite;

static Character player;
static Character demon;

static void OnPlayerCollision(byte tag)
{
    switch (tag) {
        case TAG_ENEMY:
            Character_Kill(&player);
            break;
    }
}

void GameMain()
{
    MYX_SetSpritePalette(0, SpritePalette, 3*16);

    MYX_LoadTileset(TilesetData);
    MYX_LoadTilemap(TilemapData);

    const unsigned char* map = MapInfo;
    byte px = (*map++) * MYX_TILE_WIDTH;
    byte py = (*map++) * MYX_TILE_HEIGHT;
    Character_Init(&player, px, py, SwordsmanData);

    byte demonX = 10 * MYX_TILE_WIDTH;
    byte demonY = 1 * MYX_TILE_HEIGHT;
    Character_Init(&demon, demonX, demonY, RedDemonData);
    demon.direction = DIR_LEFT;

    MYX_SetCollisionCallback(TAG_PLAYER, OnPlayerCollision);

    for (;;) {
        MYX_BeginFrame();

        Character_Draw(&demon);
        Character_ForwardBackwardMove(&demon);

        MYX_AddCollision(demon.x, demon.y, 16, 16, TAG_ENEMY);

        Character_Draw(&player);
        Character_HandleInput(&player);

        MYX_AddCollision(player.x, player.y, 16, 16, TAG_PLAYER);

        MYX_EndFrame();
    }
}
