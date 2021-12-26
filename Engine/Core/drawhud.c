/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

MYX_PFNHUDPROC MYXP_HudProcs[MAX_HUD_PROCS];
byte MYXP_HudProcCount;

void MYX_DrawHUD()
{
    for (byte i = 0; i < MYXP_HudProcCount; i++)
        MYXP_HudProcs[i]();
}
