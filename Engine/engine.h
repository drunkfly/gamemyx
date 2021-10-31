/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_H
#define ENGINE_H

#define TRANSPARENT_COLOR_INDEX4 0

#define SPRITE_FLAG_16COLOR     0x00
#define SPRITE_FLAG_256COLOR    0x01

#define STRUCT(X) struct X; typedef struct X X; struct X

typedef unsigned char byte;
typedef unsigned short word;

typedef unsigned char HSprite;

HSprite CreateSprite(const void* data, byte paletteIndex);
void DestroyAllSprites();

void SetSpritePalette(byte index, const void* data, byte count);

void PutSprite(int x, byte y, HSprite sprite);

void BeginFrame();
void EndFrame();

/* should be declared in game code. */
void GameMain();

#endif
