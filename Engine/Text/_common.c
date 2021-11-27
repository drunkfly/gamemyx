/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

Font MYXP_CurrentFont;

void MYX_SetFont(const Font* font)
{
    MYXP_CurrentFont = *font;
}
