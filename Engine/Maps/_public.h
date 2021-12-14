/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_MAPS_PUBLIC_H
#define ENGINE_MAPS_PUBLIC_H

// In small tiles
#define MYX_TILEMAP_VISIBLE_WIDTH 32
#define MYX_TILEMAP_VISIBLE_HEIGHT 24

#define MYX_TILEMAP_MAX_WIDTH 128
#define MYX_TILEMAP_MAX_HEIGHT 128

#define MYX_TILE_WIDTH 16
#define MYX_TILE_HEIGHT 16
#define MYX_TILE_SMALL_WIDTH 8
#define MYX_TILE_SMALL_HEIGHT 8

typedef enum Func {
    FUNC_NONE = 0,
    FUNC_PLAYERSTART,
    FUNC_ENEMY1,
    FUNC_ENEMY2,
    FUNC_ENEMY3,
    FUNC_ENEMY4,
    FUNC_ENEMY5,
    FUNC_ENEMY6,
    FUNC_ENEMY7,
    FUNC_ENEMY8,
    FUNC_ENEMY9,
} Func;

STRUCT(MapInfo)
{
    const byte* tilemap;
    const byte* collision;
    const byte* info;
    byte tilemapBank;
    byte collisionBank;
    byte infoBank;
};

#ifndef __SDCC
#pragma pack(push, 1)
#endif

STRUCT(MapObject)
{
    word x;
    word y;
    byte func;
    byte dir;
};

#ifndef __SDCC
#pragma pack(pop)
#endif

extern byte MYX_PlayerX;
extern byte MYX_PlayerY;

extern int MYX_MapWidth;
extern int MYX_MapHeight;

typedef void (*PFNMAPOBJECTHANDLERPROC)(const MapObject* obj);

bool MYX_IsSmallTileBlocking(byte x, byte y);

void MYX_SetMapVisibleCenter(int x, int y);

void MYX_LoadMap(const MapInfo* map, PFNMAPOBJECTHANDLERPROC handler);

#endif
