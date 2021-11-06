/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_COLLISIONS_PRIVATE_H
#define ENGINE_COLLISIONS_PRIVATE_H
#if ENABLE_COLLISION

STRUCT(MYXPCollisionRect)
{
    byte x1;
    byte y1;
    byte x2;
    byte y2;
    byte tag;
};

extern MYXCOLLISIONCALLBACK MYXP_Callbacks[MAX_COLLISION_CALLBACKS];
extern MYXPCollisionRect MYXP_Rects[MAX_COLLISION_RECTANGLES];
extern MYXPCollisionRect* MYXP_CurrentRect;

void MYXP_BeginCollisions();
void MYXP_EndCollisions();

#endif
#endif
