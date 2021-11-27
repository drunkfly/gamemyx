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
    return MYXP_CurrentFont.chars[(byte)c].xadv;
}
