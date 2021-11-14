/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_ANIMATED_SPRITES

#ifdef __SDCC
#pragma codeseg MYX_ANIMSPRITES
#pragma constseg MYX_ANIMSPRITES
#endif

MYXAnimSprite MYX_LoadAnimSprite(const void** data)
{
    const byte* p = (const byte*)*data;

    byte count = *p++;
    byte delay = *p++;
    byte palette = *p++;

    MYXAnimSprite index = MYX_CreateAnimSprite(p, count, delay, palette);
    MYXP_AdvanceSprite((const void**)&p, count);

    *data = p;

    return index;
}

#endif
