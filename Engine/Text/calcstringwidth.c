/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

byte MYX_CalcStringWidth(const char* str)
{
    byte w = 0;
    while (*str)
        w += MYX_GetCharWidth(*str++);
    return w;
}
