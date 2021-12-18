/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_SPRITES
#pragma constseg MYX_SPRITES
#endif

byte MYXP_DrawnSpriteCount;
MYXPSprite MYXP_Sprites[MYX_NEXT_MAX_SPRITES];
