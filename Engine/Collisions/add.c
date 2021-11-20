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

void MYX_AddCollision(int x, int y, byte w, byte h, byte tag)
{
    x -= MYXP_MapVisibleCenterX;
    y -= MYXP_MapVisibleCenterY;

    int x2 = x + w - 1;
    int y2 = y + h - 1;

  #if !ENABLE_COLLISION_OUTSIDE_SCREEN
    if (x < 0 || y < 0
            || x > MYX_TILEMAP_VISIBLE_WIDTH * MYX_TILE_SMALL_WIDTH
            || y > MYX_TILEMAP_VISIBLE_HEIGHT * MYX_TILE_SMALL_HEIGHT)
        return;

    if (x2 > MYX_TILEMAP_VISIBLE_WIDTH * MYX_TILE_SMALL_WIDTH)
        x2 = MYX_TILEMAP_VISIBLE_WIDTH * MYX_TILE_SMALL_WIDTH;
    if (y2 > MYX_TILEMAP_VISIBLE_HEIGHT * MYX_TILE_SMALL_HEIGHT)
        y2 = MYX_TILEMAP_VISIBLE_HEIGHT * MYX_TILE_SMALL_HEIGHT;
  #endif

    register MYXPCollisionRect* r = MYXP_CurrentRect++;
    r->x1 = x;
    r->y1 = y;
    r->x2 = x2;
    r->y2 = y2;
    r->tag = tag;
}

#endif
