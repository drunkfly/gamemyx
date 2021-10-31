/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "zxnext.h"

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
    byte w = *tilemap++;
    byte h = *tilemap++;

    byte* dst = (byte*)(0x6000 + 4 + 40 * 4);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            memcpy(dst, tilemap, w);
        }
        dst += 40;
        tilemap += w;
    }
}
