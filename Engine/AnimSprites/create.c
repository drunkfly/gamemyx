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

MYXAnimSprite MYX_CreateAnimSprite(
    const void* data, byte count, byte delay, byte paletteIndex)
{
    ASSERT(MYXP_AnimSpriteCount < MAX_ANIMATED_SPRITES);

    MYXAnimSprite index = MYXP_AnimSpriteCount++;
    MYXPAnimSprite* anim = &MYXP_AnimSprites[index];
    anim->flags = 0;
    anim->index = 0;
    anim->count = count;
    anim->delay = delay;
    anim->timer = 0;

    for (byte i = 0; i < count; i++) {
        MYXSprite sprite = MYX_CreateSprite(data, paletteIndex);
        if (i == 0)
            anim->first = sprite;
        MYXP_AdvanceSprite(&data, 1);
    }

    return index;
}

#endif
