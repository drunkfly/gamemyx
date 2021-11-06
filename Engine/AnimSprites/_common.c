/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "_private.h"
#if ENABLE_ANIMATED_SPRITES

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
        if (!sprite->visible) {
            sprite->index = 0;
            sprite->timer = 0;
        } else {
            sprite->timer++;
            if (sprite->timer >= sprite->delay) {
                sprite->timer = 0;
                sprite->index++;
                if (sprite->index >= sprite->count)
                    sprite->index = 0;
            }
        }
        sprite->visible = 0;
        ++sprite;
    }
}

#endif
