/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TILES
#pragma constseg MYX_TILES
#endif

void MYX_LoadTileset(const byte* tileset)
{
    byte paletteCount = *tileset++;
    byte n = (paletteCount << 4);
    MYX_SetTilemapPalette(0, tileset, n);
    tileset += paletteCount * 16;

    byte tileCount = *tileset++;
    memcpy((void*)0x4000, tileset, (tileCount << 5));
}

void MYX_LoadTilemap(const byte* tilemap)
{
    byte w = *tilemap++;
    byte h = *tilemap++;

    byte* dst = (byte*)(0x6000 + 4 + 40 * 4);
    for (int y = 0; y < h; y++) {
        memcpy(dst, tilemap, 32);
        dst += 40;
        tilemap += w;
    }
}
