/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_LAYER2
#pragma constseg MYX_LAYER2
#endif

void MYX_DrawLayer2Bitmap(int x, int y, const void* data, byte bank)
{
    x += MYX_SDL2_BORDER_SIZE;
    y += MYX_SDL2_BORDER_SIZE;

    const byte* p = (const byte*)data;

    byte w = *p++;
    byte h = *p++;

    word dstX = (word)x;

    Uint32* dst = &MYXP_Layer2Buffer[y * MYX_SDL2_SCREEN_WIDTH + x];

    for (byte yy = 0; yy < h; yy++) {
        ASSERT((y + yy) >= 0);
        ASSERT((y + yy) < MYX_SDL2_SCREEN_HEIGHT);

        for (byte xx = 0; xx < w; xx++) {
            ASSERT((x + xx) >= 0);
            ASSERT((x + xx) < MYX_SDL2_SCREEN_WIDTH);

            if (*p != MYX_TRANSPARENT_COLOR_INDEX8)
                *dst++ = MYXP_MapColor(*p++);
            else {
                ++dst;
                ++p;
            }
        }
        dst += MYX_SDL2_SCREEN_WIDTH - w;
    }
}
