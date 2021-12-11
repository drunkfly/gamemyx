/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_LAYER2
#pragma constseg MYX_LAYER2
#endif

void MYX_FillLayer2Rect(int x, int y, int w, byte h, byte color)
{
    x += MYX_SDL2_BORDER_SIZE;
    y += MYX_SDL2_BORDER_SIZE;

    word dstX = (word)x;

    Uint32* dst = &MYXP_Layer2Buffer[y * MYX_SDL2_SCREEN_WIDTH + x];
    Uint32 c = MYXP_MapColor(color);

    for (byte yy = 0; yy < h; yy++) {
        ASSERT((y + yy) >= 0);
        ASSERT((y + yy) < MYX_SDL2_SCREEN_HEIGHT);

        for (byte xx = 0; xx < w; xx++) {
            ASSERT((x + xx) >= 0);
            ASSERT((x + xx) < MYX_SDL2_SCREEN_WIDTH);
            *dst++ = c;
        }

        dst += MYX_SDL2_SCREEN_WIDTH - w;
    }
}
