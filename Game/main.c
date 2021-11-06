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

static const byte RedDemonIdleFrontData[] = {
#include "Data/Sprites/RedDemonIdleFront.h"
};

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

    RedDemonIdleFrontSprite = MYX_CreateSprite(RedDemonIdleFrontData, 2);

    MYX_LoadTileset(TilesetData);
    MYX_LoadTilemap(TilemapData);

    const unsigned char* map = MapInfo;
    byte px = (*map++) * MYX_TILE_WIDTH;
    byte py = (*map++) * MYX_TILE_HEIGHT;
    Character_Init(&player, px, py, SwordsmanData);

    unsigned char demonX = 5 * MYX_TILE_WIDTH;
    unsigned char demonY = 5 * MYX_TILE_HEIGHT;

    MYX_SetCollisionCallback(TAG_PLAYER, OnPlayerCollision);

    for (;;) {
        MYX_BeginFrame();

        MYX_PutSprite(demonX, demonY, RedDemonIdleFrontSprite);
        MYX_AddCollision(demonX, demonY, 16, 16, TAG_ENEMY);

        Character_Draw(&player);
        Character_HandleInput(&player);

        MYX_AddCollision(player.x, player.y, 16, 16, TAG_PLAYER);

        MYX_EndFrame();
    }
}
