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

void MYX_DestroyAllAnimSprites()
{
    MYXP_AnimSpriteCount = 0;
}

#endif
