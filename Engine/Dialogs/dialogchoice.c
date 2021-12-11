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

int MYX_DialogChoice(int speakerX, int speakerY, byte speakerH, const DialogChoice* choices)
{
    const DialogChoice* choice;
    int w = 0, h = 0;
    byte n = 0;

    for (choice = choices; choice->text; choice++, n++) {
        int choiceW = MYX_CalcStringWidth(choice->text);
        if (w < choiceW)
            w = choiceW;
        h += MYX_GetFontHeight();
    }

    w += 2 * 8;
    h += 2 * 8;

    int alignedW = (w + 7) & ~7;
    int alignedH = (h + 7) & ~7;
    int x = 8 + (alignedW - w) / 2;
    int y = 8 + (alignedH - h) / 2;

    byte chosen = 0;
    byte fontH = MYX_GetFontHeight();

    for (;;) {
        BubbleCoord coord;
        MYX_DrawSpeakerBubble(&coord, speakerX, speakerY, speakerH, w, h);

        int yy = coord.y + y, i = 0;
        for (choice = choices; choice->text; choice++, i++) {
            if (chosen == i)
                MYX_FillLayer2Rect(coord.x + 4, yy, alignedW - 8, fontH, 0xfc);

            MYX_DrawString(coord.x + x, yy, choice->text, choice->color);
            yy += fontH;
        }

        for (;;) {
            while (MYX_IsAnyKeyPressed())
                MYXP_WaitVSync();

            MYXP_WaitVSync();

            if (MYX_IsKeyPressed(KEY_Q) || MYX_IsGamepad1Pressed(GAMEPAD_UP)) {
                if (chosen == 0)
                    chosen = n - 1;
                else
                    --chosen;
                break;
            }

            if (MYX_IsKeyPressed(KEY_A) || MYX_IsGamepad1Pressed(GAMEPAD_DOWN)) {
                if (chosen == n - 1)
                    chosen = 0;
                else
                    ++chosen;
                break;
            }

            if (MYX_IsKeyPressed(KEY_SPACE) || MYX_IsGamepad1Pressed(GAMEPAD_A)) {
                if (choices[chosen].callback)
                    choices[chosen].callback();
                return chosen;
            }
        }
    }
}

#endif
