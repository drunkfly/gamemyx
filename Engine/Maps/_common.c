/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_MAPS
#pragma constseg MYX_MAPS
#endif

static const byte* MYX_CollisionMap;
static byte MYX_CollisionBank;
static byte MYX_TilemapWidth;
byte MYX_PlayerX;
byte MYX_PlayerY;

bool MYX_IsSmallTileBlocking(byte x, byte y)
{
    byte bank = MYXP_CurrentBank;
    MYXP_SetUpperMemoryBank(MYX_CollisionBank);

    byte xOff = x >> 3;
    byte xShift = x & 7;
    byte mask = MYX_CollisionMap[y * ((MYX_TilemapWidth + 7) >> 3) + xOff];
    bool result = (mask & (1 << xShift)) != 0;

    MYXP_SetUpperMemoryBank(bank);

    return result;
}

void MYX_LoadMap(const MapInfo* map)
{
    byte bank = MYXP_CurrentBank;

    MYXP_SetUpperMemoryBank(map->tilemapBank);
    MYX_TilemapWidth = *map->tilemap;
    MYX_LoadTilemap(map->tilemap);

    MYXP_SetUpperMemoryBank(map->infoBank);
    const byte* p = map->tilemap;
    MYX_PlayerX = *p++;
    MYX_PlayerY = *p++;

    MYX_CollisionMap = map->collision;
    MYX_CollisionBank = map->collisionBank;

    MYXP_SetUpperMemoryBank(bank);
}
