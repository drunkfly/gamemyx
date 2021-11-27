/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

byte MYX_DrawChar(int x, int y, char ch, byte color)
{
    x += MYX_SDL2_BORDER_SIZE;
    y += MYX_SDL2_BORDER_SIZE;

    byte firstChar = MYXP_CurrentFont.firstChar;
    if ((byte)ch < firstChar)
        return 0;

    const FontChar* p = &MYXP_CurrentFont.chars[(byte)ch - firstChar];
    const byte* img = p->pixels;

    byte w = p->w;
    byte yy = p->yoff;
    byte end = yy + p->h;

    Uint32 pixel = MYXP_MapColor(color);

    Uint32* dst = &MYXP_Layer2Buffer[(y + yy) * MYX_SDL2_SCREEN_WIDTH + x];

    for (; yy < end; yy++) {
        for (byte xx = 0; xx < w; xx++) {
            for (int i = 0; i < 8; i++) {
                if (*img & (1 << (7 - i)))
                    *dst = pixel;
                ++dst;
            }
            ++img;
        }
        dst += MYX_SDL2_SCREEN_WIDTH - w * 8;
    }

    return p->xadv;
}
