/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "zxnext.h"

static byte LastDrawnSpriteCount;
static byte DrawnSpriteCount;

static Sprite Sprites[NEXT_MAX_SPRITES];
static byte SpriteCount;

void BeginSprites()
{
    DrawnSpriteCount = 0;
    Next_SpriteControl = 0;
}

void EndSprites()
{
    for (byte i = DrawnSpriteCount; i < LastDrawnSpriteCount; i++) {
        Next_SpriteAttribute = 0; /* X */
        Next_SpriteAttribute = 0; /* Y */
        Next_SpriteAttribute = 0; /* Attribute 2 */
        Next_SpriteAttribute = 0; /* Attribute 3 */
    }

    LastDrawnSpriteCount = DrawnSpriteCount;
}

void PutSprite(int x, byte y, HSprite sprite)
{
    const Sprite* pSprite = &Sprites[sprite];
    x += 32; /* border size */
    y += 32;
    Next_SpriteAttribute = (byte)(x & 0xff);
    Next_SpriteAttribute = y;
    Next_SpriteAttribute = pSprite->attr2 | (byte)((byte)(x >> 8) & 1);
    Next_SpriteAttribute = pSprite->attr3;
    Next_SpriteAttribute = pSprite->attr4;
    ++DrawnSpriteCount;
}

HSprite CreateSprite(const void* data, byte paletteIndex)
{
    Sprite* pSprite = &Sprites[SpriteCount];
    pSprite->attr2 = (paletteIndex << 4);
    pSprite->attr3 = 0x80 | /* sprite visible */
                     0x40 | /* enable attribute byte 4 */
                     (byte)(SpriteCount & 0x3f);
    pSprite->attr4 = (SpriteCount & 0x40);

    Next_SpriteControl = SpriteCount;
    const byte* p = (const byte*)data;
    for (int i = 0; i < 16*16; i++) /* FIXME */
       Next_SpritePattern = *p++;

    return SpriteCount++;
}

void DestroyAllSprites()
{
    SpriteCount = 0;
}
