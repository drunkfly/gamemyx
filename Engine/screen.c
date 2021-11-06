/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

void MYX_BeginFrame()
{
    MYXP_BeginSprites();
    MYXP_BeginCollisions();
}

void MYX_EndFrame()
{
    MYXP_EndSprites();
    MYXP_EndCollisions();
    __asm halt __endasm;
}
