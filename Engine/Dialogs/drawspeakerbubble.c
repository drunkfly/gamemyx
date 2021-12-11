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

void MYX_DrawSpeakerBubble(BubbleCoord* outCoord, int speakerX, int speakerY, byte speakerH, word w, word h)
{
    // Transform speaker position to screen position
    speakerX -= MYXP_MapVisibleCenterX;
    speakerY -= MYXP_MapVisibleCenterY;

    // Move a bit to the left from the character
    int arrowX = speakerX;
    speakerX -= 16;

    // Do not let bubble get out of horizontal screen bounds
    int bubbleX = (speakerX >> 3);
    byte bubbleW = (w + 7) >> 3;
    if (bubbleX < -((MYX_SCREEN_BORDER_WIDTH / 2) / 8)) {
        bubbleX = -((MYX_SCREEN_BORDER_WIDTH / 2) / 8);
        speakerX = bubbleX << 3;
    }
    if (bubbleX + bubbleW >= (MYX_SCREEN_MAIN_WIDTH + (MYX_SCREEN_BORDER_WIDTH / 2)) / 8) {
        bubbleX = (MYX_SCREEN_MAIN_WIDTH + (MYX_SCREEN_BORDER_WIDTH / 2)) / 8 - bubbleW;
        speakerX = bubbleX << 3;
    }

    bool below;
    int bubbleY = speakerY;
    if (bubbleY > MYX_SCREEN_MAIN_HEIGHT / 2) {
        bubbleY -= ((h + 7) & ~7u) + 8;
        below = false;
    } else {
        bubbleY += speakerH + 8;
        below = true;
    }

    MYX_DrawBubble(speakerX, bubbleY, w, h);

    if (below) {
        MYX_DrawLayer2Bitmap(arrowX, bubbleY - 8,
            BubbleTopArrow, BUBBLETOPARROW_BANK);
        MYX_DrawLayer2Bitmap(arrowX, bubbleY,
            BubbleTopHole, BUBBLETOPHOLE_BANK);
    } else {
        arrowX += 8;
        MYX_DrawLayer2Bitmap(arrowX, speakerY - 8,
            BubbleBottomArrow, BUBBLEBOTTOMARROW_BANK);
        MYX_DrawLayer2Bitmap(arrowX, speakerY - 16,
            BubbleBottomHole, BUBBLEBOTTOMHOLE_BANK);
    }

    outCoord->x = speakerX;
    outCoord->y = bubbleY;
}

#endif
