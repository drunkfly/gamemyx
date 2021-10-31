/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_P_H
#define ENGINE_P_H

#include "engine.h"

STRUCT(Sprite)
{
    byte attr2;
    byte attr3;
    byte attr4;
};

void BeginSprites();
void EndSprites();

void PlatformInit();

#endif
