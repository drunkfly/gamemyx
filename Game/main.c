/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include <stdio.h>

enum
{
    TAG_PLAYER,
    TAG_ENEMY,
};

void gotoxy(byte x, byte y)
{
	#ifndef __WIN32__
	printf("\26%c%c", x, y);
	#endif
}

static const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
#include "Data/Palettes/RedDemonPalette.h"
};

static const byte SwordsmanIdleFrontData[] = {
#include "Data/Sprites/SwordsmanIdleFront.h"
};

static const byte SwordsmanWalkFront1Data[] = {
#include "Data/Sprites/SwordsmanWalkFront1.h"
};

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

static MYXSprite IdleFrontSprite;
static MYXSprite WalkFront1Sprite;
static MYXSprite RedDemonIdleFrontSprite;

static bool collidesWithEnemy;

static void OnPlayerCollision(byte tag)
{
    switch (tag) {
        case TAG_ENEMY:
            collidesWithEnemy = true;
            break;
    }
}

void GameMain()
{
    MYX_SetSpritePalette(0, SpritePalette, 32);
    IdleFrontSprite = MYX_CreateSprite(SwordsmanIdleFrontData, 0);
    WalkFront1Sprite = MYX_CreateSprite(SwordsmanWalkFront1Data, 0);
    RedDemonIdleFrontSprite = MYX_CreateSprite(RedDemonIdleFrontData, 1);

    MYX_LoadTileset(TilesetData);
    MYX_LoadTilemap(TilemapData);

    const unsigned char* map = MapInfo;
    unsigned char playerX = *map++;
    unsigned char playerY = *map++;

    unsigned char demonX = 5 * MYX_TILE_WIDTH;
    unsigned char demonY = 5 * MYX_TILE_HEIGHT;

    int x = playerX * MYX_TILE_WIDTH;
    int y = playerY * MYX_TILE_HEIGHT;

    MYX_SetCollisionCallback(TAG_PLAYER, OnPlayerCollision);

    for (;;) {
        MYX_BeginFrame();

        if (MYX_IsKeyPressed(KEY_O) || MYX_IsGamepad1Pressed(GAMEPAD_LEFT)) {
            if (x > 0) {
                --x;
                if (MYX_CollidesWithMap16x16(x, y))
                    ++x;
            }
        }
        if (MYX_IsKeyPressed(KEY_P) || MYX_IsGamepad1Pressed(GAMEPAD_RIGHT)) {
            if (x < 255-16) {
                ++x;
                if (MYX_CollidesWithMap16x16(x, y))
                    --x;
            }
        }
        if (MYX_IsKeyPressed(KEY_Q) || MYX_IsGamepad1Pressed(GAMEPAD_UP)) {
            if (y > 0) {
                --y;
                if (MYX_CollidesWithMap16x16(x, y))
                    ++y;
            }
        }
        if (MYX_IsKeyPressed(KEY_A) || MYX_IsGamepad1Pressed(GAMEPAD_DOWN)) {
            if (y < 192-16) {
                ++y;
                if (MYX_CollidesWithMap16x16(x, y))
                    --y;
            }
        }

        MYX_PutSprite(demonX, demonY, RedDemonIdleFrontSprite);
        MYX_AddCollision(demonX, demonY, 16, 16, TAG_ENEMY);

        MYX_PutSprite(x, y, (collidesWithEnemy ? WalkFront1Sprite : IdleFrontSprite));
        MYX_AddCollision(x, y, 16, 16, TAG_PLAYER);

        collidesWithEnemy = false;
        MYX_EndFrame();
    }
}
