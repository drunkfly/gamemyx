#include "engine_p.h"

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
