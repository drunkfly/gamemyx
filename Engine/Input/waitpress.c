/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INPUT
#pragma constseg MYX_INPUT
#endif

void MYX_WaitKeyPressed()
{
    while (!MYX_IsAnyKeyPressed())
        MYXP_WaitVSync();
}
