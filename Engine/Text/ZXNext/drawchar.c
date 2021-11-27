/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_TEXT
#pragma constseg MYX_TEXT
#endif

byte MYX_DrawChar(int x, int y, char ch, byte color)
{
    byte firstChar = MYXP_CurrentFont.firstChar;
    if ((byte)ch < firstChar)
        return 0;

    x += MYX_NEXT_BORDER_SIZE;
    y += MYX_NEXT_BORDER_SIZE;

    byte oldBank = MYXP_CurrentBank;
    MYXP_SetUpperMemoryBank(MYXP_CurrentFont.bank);

    const FontChar* p = &MYXP_CurrentFont.chars[(byte)ch - firstChar];
    const byte* img = p->pixels;

    byte w = p->w;
    byte startY = p->yoff;
    byte endY = startY + p->h;

    word dstX = (word)x;

    byte bank = (byte)(dstX >> 1);
    bank >>= 4;
    bank &= 0xfe;
    bank += ZXNEXT_LAYER2_BANK16K * 2;

    NEXT_SETREG(NEXT_MMUSLOT0, bank);
    ++bank;
    NEXT_SETREG(NEXT_MMUSLOT1, bank);

    for (byte xx = 0; xx < w; xx++) {
        for (byte i = 0; i < 8; i++) {
            byte* dst = (byte*)(startY + (byte)y + ((word)((byte)dstX & 0x3f) << 8));

            const byte* saveImg = img;

            byte pattern = (1 << (7 - i));
            for (byte yy = startY; yy < endY; yy++) {
                if (*img & pattern)
                    *dst = color;
                img += w;
                dst++;
            }

            img = saveImg;
            dstX++;

            if (((byte)dstX & 0x3f) == 0) {
                ++bank;
                NEXT_SETREG(NEXT_MMUSLOT0, bank);
                ++bank;
                NEXT_SETREG(NEXT_MMUSLOT1, bank);
            }
        }
        ++img;
    }

    byte xadv = p->xadv;

    MYXP_SetUpperMemoryBank(oldBank);
    return xadv;
}
