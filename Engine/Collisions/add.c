/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_COLLISION

void MYX_AddCollision(byte x, byte y, byte w, byte h, byte tag)
{
    register MYXPCollisionRect* r = MYXP_CurrentRect++;
    r->x1 = x;
    r->y1 = y;
    r->x2 = x + w - 1;
    r->y2 = y + h - 1;
    r->tag = tag;
}

#endif
