/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

void MYX_Cleanup()
{
    MYX_DestroyAllSprites();
  #if ENABLE_ANIMATED_SPRITES
    MYX_DestroyAllAnimSprites();
  #endif
}
