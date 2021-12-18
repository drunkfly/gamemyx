/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_SPRITES
#pragma constseg MYX_SPRITES
#endif

void MYX_PutSpriteEx(int x, int y, MYXSprite sprite, byte flags)
{
    x += MYX_NEXT_BORDER_SIZE;
    y += MYX_NEXT_BORDER_SIZE;
    x -= MYXP_MapVisibleCenterX;
    y -= MYXP_MapVisibleCenterY;

    if (x < 16 || y < 16 || x >= 256+32 || y >= 192+32)
        return;

    const MYXPSprite* pSprite = &MYXP_Sprites[sprite];
    NEXT_SpriteAttribute = (byte)(x & 0xff);
    NEXT_SpriteAttribute = y;
    NEXT_SpriteAttribute = pSprite->attr2 | (byte)((byte)(x >> 8) & 1) | flags;
    NEXT_SpriteAttribute = pSprite->attr3;
    NEXT_SpriteAttribute = pSprite->attr4;
    ++MYXP_DrawnSpriteCount;
}
