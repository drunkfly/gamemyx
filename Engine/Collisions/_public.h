/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_COLLISIONS_PUBLIC_H
#define ENGINE_COLLISIONS_PUBLIC_H
#if ENABLE_COLLISION

typedef void (*MYXCOLLISIONCALLBACK)(byte tag);

bool MYX_CollidesWithMap16x16(word x, word y);

void MYX_SetCollisionCallback(byte tag, MYXCOLLISIONCALLBACK callback);
void MYX_AddCollision(byte x, byte y, byte w, byte h, byte tag);

#endif
#endif
