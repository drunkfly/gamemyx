/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

Uint32 MYXP_TilemapPalette[256];
Uint32 MYXP_SpritePalette[256];

static Uint32 MYXP_MapColor(byte c)
{
    byte r = c >> 5;
    byte g = (c >> 2) & 7;
    byte b = c & 3;

    byte nR = (byte)((r / 7.0) * 255.0);
    byte nG = (byte)((g / 7.0) * 255.0);
    byte nB = (byte)((b / 3.0) * 255.0);

    return SDL_MapRGBA(MYXP_SDLPixelFormat, nR, nG, nB, 0xff);
}

void MYX_SetTilemapPalette(byte index, const void* data, byte count)
{
    const byte *p = (const byte*)data;
    for (byte i = 0; i < count; i++) {
        ASSERT(index + i < 256);
        MYXP_TilemapPalette[index + i] = MYXP_MapColor(*p++);
    }
}

void MYX_SetSpritePalette(byte index, const void* data, byte count)
{
    const byte *p = (const byte*)data;
    for (byte i = 0; i < count; i++) {
        ASSERT(index + i < 256);
        MYXP_SpritePalette[index + i] = MYXP_MapColor(*p++);
    }
}
