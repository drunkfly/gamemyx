/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_QUESTS

#ifdef __SDCC
#pragma codeseg MYX_QUESTS
#pragma constseg MYX_QUESTS
#endif

void MYX_DisplayNotification(const char* msg)
{
    // FIXME: need better solution

    MYX_WaitKeyReleased();

    MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
    MYX_DrawHUD();
    MYX_DrawBubble(16, 72, 224, 48);
    MYX_DrawParagraph(24, 80, msg, 198, 1);

    MYX_WaitKeyPressed();
    MYX_WaitKeyReleased();

    MYX_ClearLayer2(MYX_TRANSPARENT_COLOR_INDEX8);
    MYX_DrawHUD();
}

#endif
