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

#endif
