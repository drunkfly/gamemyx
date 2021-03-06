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

byte MYXP_AnimSpriteCount;
MYXPAnimSprite MYXP_AnimSprites[MAX_ANIMATED_SPRITES];

void MYXP_DestroyAllAnimSprites()
{
    MYXP_AnimSpriteCount = 0;
}

void MYXP_UpdateAnimSprites()
{
    MYXPAnimSprite* sprite = MYXP_AnimSprites;
    for (byte i = 0; i < MYXP_AnimSpriteCount; i++) {
        if ((sprite->flags & MYXP_ANIM_SPRITE_VISIBLE) == 0) {
            sprite->index = 0;
            sprite->timer = 0;
        } else {
            sprite->timer++;
            if (sprite->timer >= sprite->delay) {
                sprite->timer = 0;
                sprite->index++;
                if (sprite->index >= sprite->count) {
                    if ((sprite->flags & MYXP_ANIM_SPRITE_PLAY_ONCE) == 0)
                        sprite->index = 0;
                    else
                        sprite->index = sprite->count - 1;
                }
            }
        }
        sprite->flags &= ~MYXP_ANIM_SPRITE_VISIBLE;
        ++sprite;
    }
}

#endif
