/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "zxnext.h"

void MYX_SetTilemapPalette(byte index, const void* data, byte count)
{
    NEXT_SETREG(NEXT_PALETTECONTROL,
        (NEXT_GETREG(NEXT_PALETTECONTROL) & ~NEXT_IO_PALETTE_MASK)
            | NEXT_IO_TILEMAP_FIRST_PALETTE);

    NEXT_SETREG(NEXT_PALETTEINDEX, index);

    const byte* p = (const byte*)data;
    for (byte i = 0; i < count; i++)
        NEXT_SETREG(NEXT_PALETTEVALUE8, *p++);
}

void MYX_SetSpritePalette(byte index, const void* data, byte count)
{
    NEXT_SETREG(NEXT_PALETTECONTROL,
        (NEXT_GETREG(NEXT_PALETTECONTROL) & ~NEXT_IO_PALETTE_MASK)
            | NEXT_IO_SPRITES_FIRST_PALETTE);

    NEXT_SETREG(NEXT_PALETTEINDEX, index);

    const byte* p = (const byte*)data;
    for (byte i = 0; i < count; i++)
        NEXT_SETREG(NEXT_PALETTEVALUE8, *p++);
}
