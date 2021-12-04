/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_LAYER2
#pragma constseg MYX_LAYER2
#endif

void MYX_ClearLayer2(byte color)
{
    for (byte i = 0; i < ZXNEXT_LAYER2_NUM_BANKS16K * 2; i++) {
        NEXT_SETREG(NEXT_MMUSLOT0, ZXNEXT_LAYER2_BANK16K * 2 + i);
        memset((void*)0, color, 8192);
    }
}
