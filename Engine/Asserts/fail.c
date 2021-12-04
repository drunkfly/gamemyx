/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if defined(ENABLE_ASSERTIONS) && defined(TARGET_ZXNEXT)

#ifdef __SDCC
#pragma codeseg MYX_ASSERT
#pragma constseg MYX_ASSERT
#endif

void MYX_AssertFailed(const char* file, word line, const char* expr)
{
    MYX_ClearLayer2(MYX_ASSERT_BACKGROUND_COLOR);

    byte h = MYX_GetFontHeight();

    byte w1 = MYX_CalcStringWidth("File: ");
    byte w2 = MYX_CalcStringWidth("Line: ");
    byte w3 = MYX_CalcStringWidth("Expr: ");

    byte w = (w1 > w2 ? w1 : w2);
    if (w3 > w)
        w = w3;

    byte x = 5;
    byte y = 5;

    byte x1 = x + w;

    MYX_DrawString(x, y, "!! ASSERTION FAILED !!", MYX_ASSERT_TEXT_COLOR);
    y += h;
    y += h;

    MYX_DrawString(x, y, "File:", MYX_ASSERT_TEXT_COLOR);
    MYX_DrawString(x1, y, file, MYX_ASSERT_TEXT_COLOR);
    y += h;

    char lineNo[6];
    lineNo[5] = 0;
    MYX_DrawString(x, y, "Line:", MYX_ASSERT_TEXT_COLOR);
    MYX_DrawString(x1, y,
        MYX_WordToString(lineNo, line), MYX_ASSERT_TEXT_COLOR);
    y += h;

    MYX_DrawString(x, y, "Expr:", MYX_ASSERT_TEXT_COLOR);
    MYX_DrawString(x1, y, expr, MYX_ASSERT_TEXT_COLOR);
}

#endif
