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

typedef byte MYXSprite;

MYXSprite MYX_CreateSprite(const void* data, byte paletteIndex);
void MYX_DestroyAllSprites();

void MYX_LoadTileset(const byte* tileset);
void MYX_UploadVisibleTilemap(const byte* tilemap, byte x, byte y, byte w);

void MYX_SetSpritePalette(byte index, const void* data, byte count);
void MYX_SetTilemapPalette(byte index, const void* data, byte count);

void MYX_PutSprite(int x, byte y, MYXSprite sprite);

void MYX_SetTilemapOffset(byte x, byte y);

#endif
