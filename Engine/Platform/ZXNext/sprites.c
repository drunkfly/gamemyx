/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "zxnext.h"

static byte LastDrawnSpriteCount;
static byte DrawnSpriteCount;

static MYXPSprite Sprites[NEXT_MAX_SPRITES];
static byte SpriteCount;

void MYXP_BeginSprites()
{
    DrawnSpriteCount = 0;
    NEXT_SpriteControl = 0;
}

void MYXP_EndSprites()
{
    for (byte i = DrawnSpriteCount; i < LastDrawnSpriteCount; i++) {
        NEXT_SpriteAttribute = 0; /* X */
        NEXT_SpriteAttribute = 0; /* Y */
        NEXT_SpriteAttribute = 0; /* Attribute 2 */
        NEXT_SpriteAttribute = 0; /* Attribute 3 */
    }

    LastDrawnSpriteCount = DrawnSpriteCount;
}

void MYX_PutSprite(int x, byte y, MYXSprite sprite)
{
    const MYXPSprite* pSprite = &Sprites[sprite];
    x += 32; /* border size */
    y += 32;
    NEXT_SpriteAttribute = (byte)(x & 0xff);
    NEXT_SpriteAttribute = y;
    NEXT_SpriteAttribute = pSprite->attr2 | (byte)((byte)(x >> 8) & 1);
    NEXT_SpriteAttribute = pSprite->attr3;
    NEXT_SpriteAttribute = pSprite->attr4;
    ++DrawnSpriteCount;
}

MYXSprite MYX_CreateSprite(const void* data, byte paletteIndex)
{
    MYXPSprite* pSprite = &Sprites[SpriteCount];
    pSprite->attr2 = (paletteIndex << 4);
    pSprite->attr3 = 0x80 | /* sprite visible */
                     0x40 | /* enable attribute byte 4 */
                     (byte)(SpriteCount & 0x3f);
    pSprite->attr4 = 0;

    const byte* p = (const byte*)data;
    word size = NEXT_SPRITESIZE8;
    if ((*p & MYX_SPRITE_FLAG_256COLOR) == 0) { // if set, 256 color
        pSprite->attr4 = 0x80 | (SpriteCount & 0x40);
        size = NEXT_SPRITESIZE4;
    }
    p++;

    NEXT_SpriteControl = SpriteCount;
    for (word i = 0; i < size; i++)
       NEXT_SpritePattern = *p++;

    return SpriteCount++;
}

void MYXP_AdvanceSprite(const void** data, byte count)
{
    while (count-- > 0) {
        const byte* p = (const byte*)*data;
        if ((*p & MYX_SPRITE_FLAG_256COLOR) == 0)
            *data = p + (1 + NEXT_SPRITESIZE4);
        else
            *data = p + (1 + NEXT_SPRITESIZE8);
    }
}

void MYX_DestroyAllSprites()
{
    SpriteCount = 0;
}
