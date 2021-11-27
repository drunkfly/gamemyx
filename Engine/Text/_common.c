/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

const Font* MYXP_CurrentFont;
const byte* MYXP_CurrentFontBytes;

void MYX_SetFont(const Font* def, const void* bytes)
{
    MYXP_CurrentFont = def;
    MYXP_CurrentFontBytes = (const byte*)bytes;
}
