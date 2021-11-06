/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

STRUCT(MYXPCollisionRect)
{
    byte x1;
    byte y1;
    byte x2;
    byte y2;
    byte tag;
};

static MYXCOLLISIONCALLBACK Callbacks[MAX_COLLISION_CALLBACKS];
static MYXPCollisionRect Rects[MAX_COLLISION_RECTANGLES];
static MYXPCollisionRect* CurrentRect;

bool MYX_CollidesWithMap16x16(word x, word y)
{
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

void MYX_SetCollisionCallback(byte tag, MYXCOLLISIONCALLBACK callback)
{
    Callbacks[tag] = callback;
}

void MYX_AddCollision(byte x, byte y, byte w, byte h, byte tag)
{
    CurrentRect->x1 = x;
    CurrentRect->y1 = y;
    CurrentRect->x2 = x + w - 1;
    CurrentRect->y2 = y + h - 1;
    CurrentRect->tag = tag;
    CurrentRect++;
}

void MYXP_BeginCollisions()
{
    CurrentRect = Rects;
}

void MYXP_EndCollisions()
{
    // FIXME: quadratic complexity, very ineffective
    for (const MYXPCollisionRect* p1 = Rects; p1 != CurrentRect; p1++) {
        for (const MYXPCollisionRect* p2 = p1 + 1; p2 != CurrentRect; p2++) {
            if (p1->x2 >= p2->x1 && p1->x1 <= p2->x2 &&
                p1->y2 >= p2->y1 && p1->y1 <= p2->y2 &&
                p1->tag != p2->tag) {

                MYXCOLLISIONCALLBACK cb1 = Callbacks[p1->tag];
                if (cb1)
                    cb1(p2->tag);

                MYXCOLLISIONCALLBACK cb2 = Callbacks[p2->tag];
                if (cb2)
                    cb2(p1->tag);
            }
        }
    }
}
