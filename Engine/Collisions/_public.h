/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_COLLISIONS_PUBLIC_H
#define ENGINE_COLLISIONS_PUBLIC_H
#if ENABLE_COLLISION

typedef void (*MYXCOLLISIONCALLBACK)(byte tag);

bool MYX_CollidesWithMap16x16(int x, int y);

void MYX_SetCollisionCallback(byte tag, MYXCOLLISIONCALLBACK callback);
void MYX_AddCollision(int x, int y, byte w, byte h, byte tag);

#endif
#endif
