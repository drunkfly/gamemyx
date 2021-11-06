/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_ANIMATED_SPRITES

void MYX_SetAnimSpritePlayOnce(MYXAnimSprite sprite)
{
    MYXPAnimSprite* p = &MYXP_AnimSprites[sprite];
    p->flags |= MYXP_ANIM_SPRITE_PLAY_ONCE;
}

#endif
