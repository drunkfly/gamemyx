/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_DIALOGS_PUBLIC_H
#define ENGINE_DIALOGS_PUBLIC_H
#if ENABLE_DIALOGS

STRUCT(BubbleCoord)
{
    int x;
    int y;
};

void MYX_DrawBubble(int x, int y, word w, word h);
void MYX_DrawSpeakerBubble(BubbleCoord* outCoord, int speakerX, int speakerY, byte speakerH, word w, word h);
void MYX_DrawDialogBubble(int speakerX, int speakerY, byte speakerH, const char* text);

#endif
#endif
