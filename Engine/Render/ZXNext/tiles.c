/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TILES
#pragma constseg MYX_TILES
#endif

void MYX_LoadTileset(const byte* tileset, byte bank)
{
    byte oldBank = MYXP_CurrentUpperBank;
    MYXP_SetUpperMemoryBank(bank);

    byte paletteCount = *tileset++;
    byte n = (paletteCount << 4);
    MYX_SetTilemapPalette(0, tileset, n);
    tileset += paletteCount * 16;

    byte tileCount = *tileset++;
    memcpy((void*)0x4000, tileset, (tileCount << 5));

    MYXP_SetUpperMemoryBank(oldBank);
}

void MYX_UploadVisibleTilemap(const byte* tilemap, byte x, byte y, byte w)
{
    const byte BytesPerTile = 2;
    const byte TilesPerScreenRow = 40;
    const byte OffsetX = 4;
    const byte OffsetY = 4;

    byte* dst = (byte*)(0x6000
              + OffsetY * TilesPerScreenRow * BytesPerTile
              + OffsetX * BytesPerTile
              );

    const byte* p = tilemap + (y * w + x) * BytesPerTile;

    w *= BytesPerTile;
    for (int y = 0; y <= MYX_TILEMAP_VISIBLE_HEIGHT; y++) {
        memcpy(dst, p, (MYX_TILEMAP_VISIBLE_WIDTH + 1) * BytesPerTile);
        dst += TilesPerScreenRow * BytesPerTile;
        p += w;
    }
}

void MYX_SetTilemapOffset(byte x, byte y)
{
    NEXT_SETREG(NEXT_TILEMAP_X_OFFSET_LSB, x);
    NEXT_SETREG(NEXT_TILEMAP_Y_OFFSET, y);
}
