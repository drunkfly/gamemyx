/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

void MYX_BeginFrame()
{
    MYXP_BeginSprites();

  #if ENABLE_COLLISION
    MYXP_BeginCollisions();
  #endif

  #if ENABLE_ANIMATED_SPRITES
    MYXP_UpdateAnimSprites();
  #endif
}

void MYX_EndFrame()
{
  #if ENABLE_COLLISION
    MYXP_EndCollisions();
  #endif

    MYXP_EndSprites();

    MYXP_WaitVSync();
}
