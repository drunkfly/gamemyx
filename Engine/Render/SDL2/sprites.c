/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

static byte LastDrawnSpriteCount;
static byte DrawnSpriteCount;

static MYXPSprite Sprites[MYX_SDL2_MAX_SPRITES];
static byte SpriteCount;

void MYXP_BeginSprites()
{
    MYXP_RenderTilemap();
    DrawnSpriteCount = 0;
}

void MYXP_EndSprites()
{
    LastDrawnSpriteCount = DrawnSpriteCount;
}

void MYX_PutSprite(int x, int y, MYXSprite sprite)
{
    const MYXPSprite* pSprite = &Sprites[sprite];
    x -= MYXP_MapVisibleCenterX;
    y -= MYXP_MapVisibleCenterY;

    const byte* s = pSprite->data;
    bool first = true;

    for (int yy = 0; yy < pSprite->h; yy++) {
        if (y + yy >= MYX_SDL2_CONTENT_HEIGHT)
            continue;

        Uint32* p = &MYXP_ScreenBuffer[(y + yy) * MYX_SDL2_CONTENT_WIDTH + x];
        for (int xx = 0; xx < pSprite->w; xx++) {
            if (x + xx >= MYX_SDL2_CONTENT_WIDTH)
                break;

            byte index;
            if (pSprite->is256Color) {
                index = *s++;
                if (index == MYX_TRANSPARENT_COLOR_INDEX8) {
                    ++p;
                    continue;
                }
            } else {
                if (first)
                    index = (*s >> 4) & 0xF;
                else
                    index = ((*s++) & 0xF);
                first = !first;
                if (index == MYX_TRANSPARENT_COLOR_INDEX4) {
                    ++p;
                    continue;
                }
                index += pSprite->paletteIndex * 16;
            }

            if (x + xx < 0 || y + yy < 0) {
                ++p;
                continue;
            }

            *p++ = MYXP_SpritePalette[index];
        }
    }

    ++DrawnSpriteCount;
}

MYXSprite MYX_CreateSprite(const void* data, byte paletteIndex)
{
    MYXPSprite* pSprite = &Sprites[SpriteCount];

    const byte* p = (const byte*)data;
    size_t size;
    if ((*p & MYX_SPRITE_FLAG_256COLOR) == 0) { // if set, 256 color
        pSprite->is256Color = false;
        size = MYX_SDL2_SPRITESIZE4;
    } else {
        pSprite->is256Color = true;
        size = MYX_SDL2_SPRITESIZE8;
    }
    p++;

    pSprite->w = 16; // FIXME
    pSprite->h = 16;
    pSprite->paletteIndex = paletteIndex;
    memcpy(pSprite->data, p, size);

    return SpriteCount++;
}

void MYXP_AdvanceSprite(const void** data, byte count)
{
    while (count-- > 0) {
        const byte* p = (const byte*)*data;
        if ((*p & MYX_SPRITE_FLAG_256COLOR) == 0)
            *data = p + (1 + MYX_SDL2_SPRITESIZE4);
        else
            *data = p + (1 + MYX_SDL2_SPRITESIZE8);
    }
}

void MYX_DestroyAllSprites()
{
    SpriteCount = 0;
}
