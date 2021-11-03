/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#include <stdio.h>

void gotoxy(byte x, byte y)
{
	#ifndef __WIN32__
	printf("\26%c%c", x, y);
	#endif
}

static const byte SpritePalette[] = {
#include "Data/Palettes/SwordsmanPalette.h"
};

static const byte SpriteData[] = {
#include "Data/Sprites/SwordsmanIdleFront.h"
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

extern byte RawKeys[8];

void GameMain()
{
    SetSpritePalette(0, SpritePalette, 16);
    IdleFrontSprite = CreateSprite(SpriteData, 0);

    #define MAX 32
    int x = 0, y = 0;

    LoadTileset(TilesetData);
    LoadTilemap(TilemapData);

    const unsigned char* map = MapInfo;
    unsigned char playerX = *map++;
    unsigned char playerY = *map++;

    x = playerX * TILE_WIDTH;
    y = playerY * TILE_HEIGHT;

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

        PutSprite(x, y, IdleFrontSprite);

        EndFrame();
    }
}
