/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_TEXT_PUBLIC_H
#define ENGINE_TEXT_PUBLIC_H

#define MAX_FONT_CHARS 256

STRUCT(FontChar)
{
    word offset;
    byte w; /* in chars */
    byte h;
    byte yoff;
    byte xadv;
};

STRUCT(Font)
{
    byte lineH;
    byte baseline;
    FontChar chars[MAX_FONT_CHARS];
};

void MYX_SetFont(const Font* def, const void* bytes);

byte MYX_GetCharWidth(char c);
byte MYX_CalcStringWidth(const char* str);

byte MYX_DrawChar(int x, int y, char ch, byte color);
void MYX_DrawString(int x, int y, const char* str, byte color);

#endif
