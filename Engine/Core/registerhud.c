/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

void MYX_RegisterHUD(MYX_PFNHUDPROC proc) Z88DK_FASTCALL
{
    ASSERT(MYXP_HudProcCount < MAX_HUD_PROCS);
    MYXP_HudProcs[MYXP_HudProcCount++] = proc;
}
