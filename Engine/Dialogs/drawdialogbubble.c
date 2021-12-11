/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_DIALOGS

#ifdef __SDCC
#pragma codeseg MYX_DIALOGS
#pragma constseg MYX_DIALOGS
#endif

void MYX_DrawDialogBubble(int speakerX, int speakerY, byte speakerH, const char* text)
{
    int maxW = (MYX_SCREEN_BORDER_WIDTH / 2) * 2
             + MYX_SCREEN_MAIN_WIDTH
             - 2 * 8; // bubble border

    ParagraphSize size;
    MYX_CalcParagraphSize(&size, text, maxW);

    size.w += 2 * 8;
    size.h += 2 * 8;

    int w = (size.w + 7) & ~7;
    int h = (size.h + 7) & ~7;
    int x = 8 + (w - size.w) / 2;
    int y = 8 + (h - size.h) / 2;

    BubbleCoord coord;
    MYX_DrawSpeakerBubble(&coord, speakerX, speakerY, speakerH, size.w, size.h);

    MYX_DrawParagraph(coord.x + x, coord.y + y, text, maxW, 1); // black
}

#endif
