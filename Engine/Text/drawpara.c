/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

void MYX_DrawParagraph(int x, int y, const char* str, int maxW, int color)
{
    byte spaceW = MYX_GetCharWidth(' ');
    byte fontH = MYX_GetFontHeight();
    int lineW = 0;

    const char* p = str;
    for (;;) {
        const char* end = p;
        while (*end != 0 && *end != ' ' && *end != '\n')
            ++end;

        // p => word start
        // end => word end

        bool newLine = false;

        int wordW = 0;
        for (const char* ptr = p; ptr != end; ++ptr)
            wordW += MYX_GetCharWidth(*ptr);

        if (lineW == 0) {
            for (const char* ptr = p; ptr != end; ++ptr)
                lineW += MYX_DrawChar(x + lineW, y, *ptr, color); 
        } else {
            if (lineW + spaceW + wordW > maxW)
                newLine = true;
            else {
                lineW += spaceW;
                for (const char* ptr = p; ptr != end; ++ptr)
                    lineW += MYX_DrawChar(x + lineW, y, *ptr, color); 
            }
        }

        if (*end == 0)
            break;

        if (newLine || *end == '\n') {
            y += fontH;
            lineW = 0;
        }

        p = end + 1;
    }
}
