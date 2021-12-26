/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

void MYX_DrawString(int x, int y, const char* str, byte color)
{
    while (*str)
        x += MYX_DrawChar(x, y, *str++, color);
}
