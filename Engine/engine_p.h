/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_P_H
#define ENGINE_P_H

#include "engine.h"

STRUCT(MYXPSprite)
{
    byte attr2;
    byte attr3;
    byte attr4;
};

void MYXP_BeginSprites();
void MYXP_EndSprites();

void MYXP_BeginCollisions();
void MYXP_EndCollisions();

void MYXP_PlatformInit();

#endif
