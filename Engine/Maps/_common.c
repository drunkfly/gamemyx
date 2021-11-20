/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_MAPS
#pragma constseg MYX_MAPS
#endif

static const byte* MYX_TileMap;
static const byte* MYX_CollisionMap;
static byte MYX_CollisionBank;
static byte MYX_TilemapBank;
static byte MYX_TilemapWidth;
static byte MYX_TilemapHeight;
static byte MYX_TileScrollX;
static byte MYX_TileScrollY;
static int MYX_TilemapMaxScrollX;
static int MYX_TilemapMaxScrollY;
byte MYX_PlayerX;
byte MYX_PlayerY;

bool MYX_IsSmallTileBlocking(byte x, byte y)
{
    const byte* collisionMap = MYX_CollisionMap;

  #ifdef TARGET_ZXNEXT
    byte bank = MYXP_CurrentBank;
    MYXP_SetUpperMemoryBank(MYX_CollisionBank);
  #endif

    byte xOff = x >> 3;
    byte xShift = x & 7;
    byte mask = collisionMap[y * ((MYX_TilemapWidth + 7) >> 3) + xOff];
    bool result = (mask & (1 << xShift)) != 0;

  #ifdef TARGET_ZXNEXT
    MYXP_SetUpperMemoryBank(bank);
  #endif

    return result;
}

void MYX_SetMapVisibleCenter(int x, int y)
{
    x -= (MYX_TILEMAP_VISIBLE_WIDTH  / 2) * MYX_TILE_WIDTH;
    y -= (MYX_TILEMAP_VISIBLE_HEIGHT / 2) * MYX_TILE_HEIGHT;

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;

    if (x > MYX_TilemapMaxScrollX)
        x = MYX_TilemapMaxScrollX;
    if (y > MYX_TilemapMaxScrollY)
        y = MYX_TilemapMaxScrollY;

    MYX_SetTilemapOffset((byte)x & 7, (byte)y & 7);

    byte scrollX = (byte)(x >> 3) & 0xff;
    byte scrollY = (byte)(y >> 3) & 0xff;
    if (scrollX != MYX_TileScrollX || scrollY != MYX_TileScrollY) {
        MYX_TileScrollX = scrollX;
        MYX_TileScrollY = scrollY;
        byte w = MYX_TilemapWidth;

      #ifdef TARGET_ZXNEXT
        byte bank = MYXP_CurrentBank;
        MYXP_SetUpperMemoryBank(MYX_TilemapBank);
      #endif

        MYX_UploadVisibleTilemap(MYX_TileMap, scrollX, scrollY, w);

      #ifdef TARGET_ZXNEXT
        MYXP_SetUpperMemoryBank(bank);
      #endif
    }
}

void MYX_LoadMap(const MapInfo* map)
{
  #ifdef TARGET_ZXNEXT
    byte bank = MYXP_CurrentBank;
  #endif

    MYX_CollisionMap = map->collision;
    MYX_CollisionBank = map->collisionBank;
    MYX_TileMap = map->tilemap;
    MYX_TilemapBank = map->tilemapBank;
    const byte* info = map->info;
    byte infoBank = map->infoBank;

    ASSERT(MYX_TilemapWidth >= MYX_TILEMAP_VISIBLE_WIDTH);
    ASSERT(MYX_TilemapHeight >= MYX_TILEMAP_VISIBLE_HEIGHT);
    ASSERT(MYX_TilemapWidth < MYX_TILEMAP_MAX_WIDTH);
    ASSERT(MYX_TilemapHeight < MYX_TILEMAP_MAX_HEIGHT);

  #ifdef TARGET_ZXNEXT
    MYXP_SetUpperMemoryBank(MYX_TilemapBank);
  #endif
    byte w = *MYX_TileMap++;
    byte h = *MYX_TileMap++;
    MYX_UploadVisibleTilemap(MYX_TileMap, 0, 0, w);

  #ifdef TARGET_ZXNEXT
    MYXP_SetUpperMemoryBank(infoBank);
  #endif
    byte playerX = *info++;
    byte playerY = *info++;

  #ifdef TARGET_ZXNEXT
    MYXP_SetUpperMemoryBank(bank);
  #endif

    MYX_PlayerX = playerX;
    MYX_PlayerY = playerY;
    MYX_TilemapWidth = w;
    MYX_TilemapHeight = h;
    MYX_TilemapMaxScrollX = (w - MYX_TILEMAP_VISIBLE_WIDTH) * MYX_TILE_WIDTH;
    MYX_TilemapMaxScrollY = (h - MYX_TILEMAP_VISIBLE_WIDTH) * MYX_TILE_HEIGHT;
    MYX_TileScrollX = 0;
    MYX_TileScrollY = 0;
}
