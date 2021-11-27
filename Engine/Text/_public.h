/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_TEXT_PUBLIC_H
#define ENGINE_TEXT_PUBLIC_H

#define MAX_FONT_CHARS 256

STRUCT(FontChar)
{
    const byte* pixels;
    byte w; /* in chars */
    byte h;
    byte yoff;
    byte xadv;
};

STRUCT(Font)
{
    byte lineH;
    byte baseline;
    byte firstChar;
    byte bank;
    const FontChar* chars;
};

void MYX_SetFont(const Font* font);

byte MYX_GetCharWidth(char c);
byte MYX_CalcStringWidth(const char* str);

byte MYX_DrawChar(int x, int y, char ch, byte color);
void MYX_DrawString(int x, int y, const char* str, byte color);

#endif
