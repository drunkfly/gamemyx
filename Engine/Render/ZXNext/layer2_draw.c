/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_LAYER2
#pragma constseg MYX_LAYER2
#endif

void MYX_DrawLayer2Bitmap(int x, int y, const void* data, byte bank)
{
    x += MYX_NEXT_BORDER_SIZE;
    y += MYX_NEXT_BORDER_SIZE;

    byte oldBank = MYXP_CurrentUpperBank;
    MYXP_SetUpperMemoryBank(bank);

    const byte* p = (const byte*)data;

    byte w = *p++;
    byte h = *p++;

    word dstX = (word)x;

    byte layer2Bank = (byte)(dstX >> 1);
    layer2Bank >>= 4;
    layer2Bank &= 0xfe;
    layer2Bank += ZXNEXT_LAYER2_BANK16K * 2;

    NEXT_SETREG(NEXT_MMUSLOT0, layer2Bank);
    ++layer2Bank;
    NEXT_SETREG(NEXT_MMUSLOT1, layer2Bank);

    for (byte xx = 0; xx < w; xx++) {
        byte* dst = (byte*)(y + ((word)((byte)dstX & 0x3f) << 8));

        const byte* saveP = p;

        for (byte yy = 0; yy < h; yy++) {
            *dst = *p;
            p += w;
            dst++;
        }

        p = saveP;
        dstX++;

        if (((byte)dstX & 0x3f) == 0) {
            ++layer2Bank;
            NEXT_SETREG(NEXT_MMUSLOT0, layer2Bank);
            ++layer2Bank;
            NEXT_SETREG(NEXT_MMUSLOT1, layer2Bank);
        }

        ++p;
    }

    MYXP_SetUpperMemoryBank(oldBank);
}
