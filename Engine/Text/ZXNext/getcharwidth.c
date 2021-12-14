/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

byte MYX_GetCharWidth(char c)
{
    byte firstChar = MYXP_CurrentFont.firstChar;
    if ((byte)c < firstChar)
        return 0;

    byte oldBank = MYXP_CurrentUpperBank;
    MYXP_SetUpperMemoryBank(MYXP_CurrentFont.bank);

    byte w = MYXP_CurrentFont.chars[(byte)c - firstChar].xadv;

    MYXP_SetUpperMemoryBank(oldBank);
    return w;
}
