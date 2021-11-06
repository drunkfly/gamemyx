/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <string.h>
#include "../../config.h"

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

void MYX_Cleanup();

/**********************************************************************/
/* Input */

#ifdef ZXNEXT
#include "../Platform/ZXNext/keys.h"
#endif

bool MYX_IsKeyPressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((d, e, iyl, iyh));

bool MYX_IsGamepad1Pressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((b, c, d, e, h, iyl, iyh));

bool MYX_IsGamepad2Pressed(byte key)
    Z88DK_FASTCALL Z88DK_PRESERVES((b, c, d, e, h, iyl, iyh));

/**********************************************************************/
/* Tiles */

#define MYX_TILE_WIDTH 16
#define MYX_TILE_HEIGHT 16
#define MYX_TILE_SMALL_WIDTH 8
#define MYX_TILE_SMALL_HEIGHT 8

void MYX_SetTilemapPalette(byte index, const void* data, byte count);

bool MYX_IsSmallTileBlocking(byte x, byte y);

void MYX_LoadTileset(const byte* tileset);
void MYX_LoadTilemap(const byte* tilemap);

/**********************************************************************/
/* Sprites */

#define MYX_TRANSPARENT_COLOR_INDEX4    0

#define MYX_SPRITE_FLAG_16COLOR         0x00
#define MYX_SPRITE_FLAG_256COLOR        0x01

typedef byte MYXSprite;

MYXSprite MYX_CreateSprite(const void* data, byte paletteIndex);
void MYX_DestroyAllSprites();

void MYX_SetSpritePalette(byte index, const void* data, byte count);

void MYX_PutSprite(int x, byte y, MYXSprite sprite);

#include "../AnimSprites/_public.h"
#include "../Collisions/_public.h"

/**********************************************************************/

void MYX_BeginFrame();
void MYX_EndFrame();

/* should be declared in game code. */
void GameMain();

#endif
