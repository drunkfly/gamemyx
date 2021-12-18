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

void MYX_PutAnimSpriteEx(int x, int y, MYXAnimSprite sprite, byte flags)
{
    MYXPAnimSprite* p = &MYXP_AnimSprites[sprite];
    MYX_PutSpriteEx(x, y, p->first + p->index, flags);
    p->flags |= MYXP_ANIM_SPRITE_VISIBLE;
}

#endif
