/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

void MYX_ClearLayer2(byte color)
{
    Uint32 pixel = MYXP_MapColor(color);

    Uint32* dst = MYXP_Layer2Buffer;
    Uint32* end = dst + MYX_SDL2_SCREEN_WIDTH * MYX_SDL2_SCREEN_HEIGHT;

    while (dst < end)
        *dst++ = pixel;
}
