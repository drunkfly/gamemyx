#include "engine_p.h"

STRUCT(CollisionRect)
{
    byte x1;
    byte y1;
    byte x2;
    byte y2;
    byte tag;
};

static PFNCOLLISIONCALLBACK callbacks[MAX_COLLISION_CALLBACKS];
static CollisionRect rects[MAX_COLLISION_RECTANGLES];
static CollisionRect* currentRect;

bool CollidesWithMap16x16(word x, word y)
{
    word tileX = x >> 3;
    word tileY = y >> 3;

    if (IsSmallTileBlocking(tileX, tileY))
        return true;
    if (IsSmallTileBlocking(tileX + 1, tileY))
        return true;
    if (IsSmallTileBlocking(tileX, tileY + 1))
        return true;
    if (IsSmallTileBlocking(tileX + 1, tileY + 1))
        return true;

    if ((x & 7) != 0) {
        if (IsSmallTileBlocking(tileX + 2, tileY))
            return true;
        if (IsSmallTileBlocking(tileX + 2, tileY + 1))
            return true;
        if ((y & 7) != 0 && IsSmallTileBlocking(tileX + 2, tileY + 2))
            return true;
    }

    if ((y & 7) != 0) {
        if (IsSmallTileBlocking(tileX, tileY + 2))
            return true;
        if (IsSmallTileBlocking(tileX + 1, tileY + 2))
            return true;
    }

    return false;
}

void SetCollisionCallback(byte tag, PFNCOLLISIONCALLBACK callback)
{
    callbacks[tag] = callback;
}

void AddCollision(byte x, byte y, byte w, byte h, byte tag)
{
    currentRect->x1 = x;
    currentRect->y1 = y;
    currentRect->x2 = x + w - 1;
    currentRect->y2 = y + h - 1;
    currentRect->tag = tag;
    currentRect++;
}

void BeginCollisions()
{
    currentRect = rects;
}

void EndCollisions()
{
    // FIXME: quadratic complexity, very ineffective
    for (const CollisionRect* p1 = rects; p1 != currentRect; p1++) {
        for (const CollisionRect* p2 = p1 + 1; p2 != currentRect; p2++) {
            if (p1->x2 >= p2->x1 && p1->x1 <= p2->x2 &&
                p1->y2 >= p2->y1 && p1->y1 <= p2->y2 &&
                p1->tag != p2->tag) {

                PFNCOLLISIONCALLBACK cb1 = callbacks[p1->tag];
                if (cb1)
                    cb1(p2->tag);

                PFNCOLLISIONCALLBACK cb2 = callbacks[p2->tag];
                if (cb2)
                    cb2(p1->tag);
            }
        }
    }
}
