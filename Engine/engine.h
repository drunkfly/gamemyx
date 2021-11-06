/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <string.h>
#include "../config.h"

/**********************************************************************/
/* Common */

#define STRUCT(X) \
    struct X; \
    typedef struct X X; \
    struct X

#ifdef ZXNEXT
 #define Z88DK_FASTCALL __z88dk_fastcall
 #define Z88DK_PRESERVES(REGS) __preserves_regs REGS
#else
 #define Z88DK_FASTCALL
 #define Z88DK_PRESERVES(REGS)
#endif

typedef unsigned char byte;
typedef unsigned short word;

/**********************************************************************/
/* Input */

#ifdef ZXNEXT
#include "Platform/ZXNext/keys.h"
#endif

bool IsKeyPressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((d, e, iyl, iyh));

bool IsGamepad1Pressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((b, c, d, e, h, iyl, iyh));

bool IsGamepad2Pressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((b, c, d, e, h, iyl, iyh));

/**********************************************************************/
/* Tiles */

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define TILE_SMALL_WIDTH 8
#define TILE_SMALL_HEIGHT 8

void SetTilemapPalette(byte index, const void* data, byte count);

bool IsSmallTileBlocking(byte x, byte y);

void LoadTileset(const byte* tileset);
void LoadTilemap(const byte* tilemap);

/**********************************************************************/
/* Sprites */

#define TRANSPARENT_COLOR_INDEX4 0

#define SPRITE_FLAG_16COLOR     0x00
#define SPRITE_FLAG_256COLOR    0x01

typedef byte HSprite;

HSprite CreateSprite(const void* data, byte paletteIndex);
void DestroyAllSprites();

void SetSpritePalette(byte index, const void* data, byte count);

void PutSprite(int x, byte y, HSprite sprite);

/**********************************************************************/
/* Collisions */

typedef void (*PFNCOLLISIONCALLBACK)(byte tag);

bool CollidesWithMap16x16(word x, word y);

void SetCollisionCallback(byte tag, PFNCOLLISIONCALLBACK callback);

void AddCollision(byte x, byte y, byte w, byte h, byte tag);

/**********************************************************************/

void BeginFrame();
void EndFrame();

/* should be declared in game code. */
void GameMain();

#endif
