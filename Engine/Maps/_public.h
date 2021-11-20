/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_MAPS_PUBLIC_H
#define ENGINE_MAPS_PUBLIC_H

#define MYX_TILE_WIDTH 16
#define MYX_TILE_HEIGHT 16
#define MYX_TILE_SMALL_WIDTH 8
#define MYX_TILE_SMALL_HEIGHT 8

STRUCT(MapInfo)
{
    const byte* tilemap;
    const byte* collision;
    const byte* info;
    byte tilemapBank;
    byte collisionBank;
    byte infoBank;
};

extern byte MYX_PlayerX;
extern byte MYX_PlayerY;

bool MYX_IsSmallTileBlocking(byte x, byte y);

void MYX_LoadMap(const MapInfo* map);

#endif