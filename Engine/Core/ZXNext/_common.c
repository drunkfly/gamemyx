/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

byte MYXP_CurrentUpperBank;
byte MYXP_CurrentLowerBank;

void MYXP_SetUpperMemoryBank(byte bank) Z88DK_FASTCALL
{
    byte page = (bank << 1);
    MYXP_CurrentUpperBank = bank;
    NEXT_SETREG(NEXT_MMUSLOT6, page);
    ++page;
    NEXT_SETREG(NEXT_MMUSLOT7, page);
}

void MYXP_SetLowerMemoryBank(byte bank) Z88DK_FASTCALL
{
    byte page = (bank << 1);
    MYXP_CurrentLowerBank = bank;
    NEXT_SETREG(NEXT_MMUSLOT2, page);
    ++page;
    NEXT_SETREG(NEXT_MMUSLOT3, page);
}

void MYXP_WaitVSync()
{
    __asm halt __endasm;
}
