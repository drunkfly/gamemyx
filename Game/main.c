/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
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

static HSprite IdleFrontSprite;
static HSprite WalkFront1Sprite;
static HSprite RedDemonIdleFrontSprite;

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
    SetSpritePalette(0, SpritePalette, 32);
    IdleFrontSprite = CreateSprite(SwordsmanIdleFrontData, 0);
    WalkFront1Sprite = CreateSprite(SwordsmanWalkFront1Data, 0);
    RedDemonIdleFrontSprite = CreateSprite(RedDemonIdleFrontData, 1);

    LoadTileset(TilesetData);
    LoadTilemap(TilemapData);

    const unsigned char* map = MapInfo;
    unsigned char playerX = *map++;
    unsigned char playerY = *map++;

    unsigned char demonX = 5 * TILE_WIDTH;
    unsigned char demonY = 5 * TILE_HEIGHT;

    int x = playerX * TILE_WIDTH;
    int y = playerY * TILE_HEIGHT;

    SetCollisionCallback(TAG_PLAYER, OnPlayerCollision);

    for (;;) {
        BeginFrame();

        if (IsKeyPressed(KEY_O) || IsGamepad1Pressed(GAMEPAD_LEFT)) {
            if (x > 0) {
                --x;
                if (CollidesWithMap16x16(x, y))
                    ++x;
            }
        }
        if (IsKeyPressed(KEY_P) || IsGamepad1Pressed(GAMEPAD_RIGHT)) {
            if (x < 255-16) {
                ++x;
                if (CollidesWithMap16x16(x, y))
                    --x;
            }
        }
        if (IsKeyPressed(KEY_Q) || IsGamepad1Pressed(GAMEPAD_UP)) {
            if (y > 0) {
                --y;
                if (CollidesWithMap16x16(x, y))
                    ++y;
            }
        }
        if (IsKeyPressed(KEY_A) || IsGamepad1Pressed(GAMEPAD_DOWN)) {
            if (y < 192-16) {
                ++y;
                if (CollidesWithMap16x16(x, y))
                    --y;
            }
        }

        PutSprite(demonX, demonY, RedDemonIdleFrontSprite);
        AddCollision(demonX, demonY, 16, 16, TAG_ENEMY);

        PutSprite(x, y, (collidesWithEnemy ? WalkFront1Sprite : IdleFrontSprite));
        AddCollision(x, y, 16, 16, TAG_PLAYER);

        collidesWithEnemy = false;
        EndFrame();
    }
}
