/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_ANIMATED_SPRITES

void MYX_PutAnimSprite(int x, byte y, MYXAnimSprite sprite)
{
    MYXPAnimSprite* p = &MYXP_AnimSprites[sprite];
    MYX_PutSprite(x, y, p->first + p->index);
    p->visible = 1;
}

#endif
