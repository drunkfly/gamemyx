/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INTERRUPT
#pragma constseg MYX_INTERRUPT
#endif

void MYXP_ReadInput() __preserves_regs(a, iyl, iyh);

void MYXP_InterruptHandler()
{
    MYXP_ReadInput();
}
