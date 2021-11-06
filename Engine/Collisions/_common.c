/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_COLLISION

MYXCOLLISIONCALLBACK MYXP_Callbacks[MAX_COLLISION_CALLBACKS];
MYXPCollisionRect MYXP_Rects[MAX_COLLISION_RECTANGLES];
MYXPCollisionRect* MYXP_CurrentRect;

void MYXP_BeginCollisions()
{
    MYXP_CurrentRect = MYXP_Rects;
}

void MYXP_EndCollisions()
{
    // FIXME: quadratic complexity, very ineffective
    const MYXPCollisionRect* end = MYXP_CurrentRect;
    for (const MYXPCollisionRect* p1 = MYXP_Rects; p1 != end; p1++) {
        for (const MYXPCollisionRect* p2 = p1 + 1; p2 != end; p2++) {
            if (p1->x2 >= p2->x1 && p1->x1 <= p2->x2 &&
                p1->y2 >= p2->y1 && p1->y1 <= p2->y2 &&
                p1->tag != p2->tag) {

                MYXCOLLISIONCALLBACK cb1 = MYXP_Callbacks[p1->tag];
                if (cb1)
                    cb1(p2->tag);

                MYXCOLLISIONCALLBACK cb2 = MYXP_Callbacks[p2->tag];
                if (cb2)
                    cb2(p1->tag);
            }
        }
    }
}

#endif
