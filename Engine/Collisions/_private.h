/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_COLLISIONS_PRIVATE_H
#define ENGINE_COLLISIONS_PRIVATE_H
#if ENABLE_COLLISION

STRUCT(MYXPCollisionRect)
{
  #if ENABLE_COLLISION_OUTSIDE_SCREEN
    int x1;
    int y1;
    int x2;
    int y2;
  #else
    byte x1;
    byte y1;
    byte x2;
    byte y2;
  #endif
    byte tag;
};

extern MYXCOLLISIONCALLBACK MYXP_Callbacks[MAX_COLLISION_CALLBACKS];
extern MYXPCollisionRect MYXP_Rects[MAX_COLLISION_RECTANGLES];
extern MYXPCollisionRect* MYXP_CurrentRect;

void MYXP_BeginCollisions();
void MYXP_EndCollisions();

#endif
#endif
