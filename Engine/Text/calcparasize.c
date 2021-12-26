/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

void MYX_CalcParagraphSize(ParagraphSize* outSize, const char* str, int maxW)
{
    ParagraphSize size;
    byte spaceW = MYX_GetCharWidth(' ');
    byte fontH = MYX_GetFontHeight();
    int lineW = 0;

    size.w = 0;
    size.h = 0;

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

        if (lineW == 0)
            lineW = wordW;
        else {
            if (lineW + spaceW + wordW > maxW)
                newLine = true;
            else
                lineW += spaceW + wordW;
        }

        if (*end == 0) {
            if (lineW > 0) {
                if (size.w < lineW)
                    size.w = lineW;
                size.h += fontH;
            }
            break;
        }

        if (newLine || *end == '\n') {
            if (size.w < lineW)
                size.w = lineW;
            size.h += fontH;
            lineW = 0;
        }

        p = end + 1;
    }

    *outSize = size;
}
