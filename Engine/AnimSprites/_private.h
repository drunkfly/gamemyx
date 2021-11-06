/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_ANIMSPRITES_PRIVATE_H
#define ENGINE_ANIMSPRITES_PRIVATE_H

#include "engine_p.h"

STRUCT(MYXPAnimSprite)
{
    MYXSprite first;
    byte visible;
    byte index;
    byte count;
    byte delay;
    byte timer;
};

extern byte MYXP_AnimSpriteCount;
extern MYXPAnimSprite MYXP_AnimSprites[MAX_ANIMATED_SPRITES];

void MYXP_DestroyAllAnimSprites();
void MYXP_UpdateAnimSprites();

#endif
