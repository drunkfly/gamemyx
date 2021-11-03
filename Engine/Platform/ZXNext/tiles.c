/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "zxnext.h"

static byte tilemapWidth;
static const byte* collisionMap;

bool IsSmallTileBlocking(byte x, byte y)
{
    byte xOff = x >> 3;
    byte xShift = x & 7;
    byte mask = collisionMap[y * ((tilemapWidth + 7) >> 3) + xOff];
    return (mask & (1 << xShift)) != 0;
}

void LoadTileset(const byte* tileset)
{
    byte paletteCount = *tileset++;
    byte n = (paletteCount << 4);
    SetTilemapPalette(0, tileset, n);
    tileset += paletteCount * 16;

    byte tileCount = *tileset++;
    memcpy((void*)0x4000, tileset, (tileCount << 5));
}

void LoadTilemap(const byte* tilemap)
{
    tilemapWidth = *tilemap++;
    byte h = *tilemap++;

    byte* dst = (byte*)(0x6000 + 4 + 40 * 4);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < tilemapWidth; x++)
            memcpy(dst, tilemap, tilemapWidth);
        dst += 40;
        tilemap += tilemapWidth;
    }

    collisionMap = tilemap;
}
