/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

byte MYXP_CurrentBank;

void MYXP_SetUpperMemoryBank(byte bank)
{
    byte page = (bank << 1);
    NEXT_SETREG(NEXT_MMUSLOT6, page);
    ++page;
    NEXT_SETREG(NEXT_MMUSLOT7, page);
    MYXP_CurrentBank = bank;
}

void MYXP_WaitVSync()
{
    __asm halt __endasm;
}
