/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

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

    __asm halt __endasm;
}

void MYX_Cleanup()
{
    MYX_DestroyAllSprites();
  #if ENABLE_ANIMATED_SPRITES
    MYXP_DestroyAllAnimSprites();
  #endif
}

void MYXP_EngineMain()
{
    MYXP_PlatformInit();

    GameMain();

    for (;;) {}
}
