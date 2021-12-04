/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

byte MYX_GetCharWidth(char c)
{
    byte firstChar = MYXP_CurrentFont.firstChar;
    if ((byte)c < firstChar)
        return 0;

    return MYXP_CurrentFont.chars[(byte)c - firstChar].xadv;
}
