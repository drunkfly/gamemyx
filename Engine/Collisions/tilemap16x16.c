/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_COLLISION

#ifdef __SDCC
#pragma codeseg MYX_COLLISIONS
#pragma constseg MYX_COLLISIONS
#endif

bool MYX_CollidesWithMap16x16(int x, int y)
{
    if (x < 0 || y < 0)
        return true;

    word tileX = x >> 3;
    word tileY = y >> 3;

    if (MYX_IsSmallTileBlocking(tileX, tileY))
        return true;
    if (MYX_IsSmallTileBlocking(tileX + 1, tileY))
        return true;
    if (MYX_IsSmallTileBlocking(tileX, tileY + 1))
        return true;
    if (MYX_IsSmallTileBlocking(tileX + 1, tileY + 1))
        return true;

    if ((x & 7) != 0) {
        if (MYX_IsSmallTileBlocking(tileX + 2, tileY))
            return true;
        if (MYX_IsSmallTileBlocking(tileX + 2, tileY + 1))
            return true;
        if ((y & 7) != 0 && MYX_IsSmallTileBlocking(tileX + 2, tileY + 2))
            return true;
    }

    if ((y & 7) != 0) {
        if (MYX_IsSmallTileBlocking(tileX, tileY + 2))
            return true;
        if (MYX_IsSmallTileBlocking(tileX + 1, tileY + 2))
            return true;
    }

    return false;
}

#endif
