/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#include "DialogAssets/BubbleBitmaps.h"
#if ENABLE_DIALOGS

#ifdef __SDCC
#pragma codeseg MYX_DIALOGS
#pragma constseg MYX_DIALOGS
#endif

void MYX_DrawBubble(int x, int y, word w, word h)
{
    byte bW = (w + 7) >> 3;
    byte bH = (h + 7) >> 3;

    if (bW < 2)
        bW = 2;
    if (bH < 2)
        bH = 2;

    bH -= 2;
    bW -= 2;

    MYX_DrawLayer2Bitmap(x, y, BubbleTopLeft, BUBBLETOPLEFT_BANK);
    MYX_DrawLayer2Bitmap(x + ((bW + 1) << 3), y, BubbleTopRight, BUBBLETOPRIGHT_BANK);
    MYX_DrawLayer2Bitmap(x, y + ((bH + 1) << 3), BubbleBottomLeft, BUBBLEBOTTOMLEFT_BANK);
    MYX_DrawLayer2Bitmap(x + ((bW + 1) << 3), y + ((bH + 1) << 3), BubbleBottomRight, BUBBLEBOTTOMRIGHT_BANK);

    for (byte yy = 0; yy < bH; ++yy) {
        int curY = y + ((yy + 1) << 3);

        MYX_DrawLayer2Bitmap(x, curY, BubbleLeft, BUBBLELEFT_BANK);
        MYX_DrawLayer2Bitmap(x + ((bW + 1) << 3), curY,
            BubbleRight, BUBBLELEFT_BANK);
       
        for (byte xx = 0; xx < bW; ++xx) {
            MYX_DrawLayer2Bitmap(x + ((xx + 1) << 3), curY,
                BubbleCenter, BUBBLECENTER_BANK);
        }
    }

    for (byte xx = 0; xx < bW; ++xx) {
        int curX = x + ((xx + 1) << 3);
        MYX_DrawLayer2Bitmap(curX, y, BubbleTop, BUBBLETOP_BANK);
        MYX_DrawLayer2Bitmap(curX, y + ((bH + 1) << 3),
            BubbleBottom, BUBBLEBOTTOM_BANK);
    }
}

#endif
