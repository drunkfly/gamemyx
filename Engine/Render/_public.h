/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_RENDER_PUBLIC_H
#define ENGINE_RENDER_PUBLIC_H

#define MYX_TRANSPARENT_COLOR_INDEX4    0
#define MYX_TRANSPARENT_COLOR_INDEX8    0

#define MYX_SPRITE_FLAG_16COLOR         0x00
#define MYX_SPRITE_FLAG_256COLOR        0x01

#define MYX_FLIP_X                      8
#define MYX_FLIP_Y                      4

#define MYX_SCREEN_MAIN_WIDTH           256
#define MYX_SCREEN_MAIN_HEIGHT          192
#define MYX_SCREEN_BORDER_WIDTH         32
#define MYX_SCREEN_BORDER_HEIGHT        32
#define MYX_SCREEN_FULL_WIDTH           (MYX_SCREEN_MAIN_WIDTH + MYX_SCREEN_BORDER_WIDTH * 2)
#define MYX_SCREEN_FULL_HEIGHT          (MYX_SCREEN_MAIN_HEIGHT + MYX_SCREEN_BORDER_HEIGHT * 2)

typedef byte MYXSprite;

MYXSprite MYX_CreateSprite(const void* data, byte paletteIndex);
void MYX_DestroyAllSprites();

void MYX_LoadTileset(const byte* tileset);
void MYX_UploadVisibleTilemap(const byte* tilemap, byte x, byte y, byte w);

void MYX_SetSpritePalette(byte index, const void* data, byte count);
void MYX_SetTilemapPalette(byte index, const void* data, byte count);

void MYX_PutSprite(int x, int y, MYXSprite sprite);
void MYX_PutSpriteEx(int x, int y, MYXSprite sprite, byte flags);

void MYX_SetTilemapOffset(byte x, byte y);

void MYX_ClearLayer2(byte color);
void MYX_DrawLayer2Bitmap(int x, int y, const void* data, byte bank);
void MYX_FillLayer2Rect(int x, int y, int w, byte h, byte color);

#endif
