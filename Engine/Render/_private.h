/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_RENDER_PRIVATE_H
#define ENGINE_RENDER_PRIVATE_H

STRUCT(MYXPSprite)
{
    byte attr2;
    byte attr3;
    byte attr4;
};

void MYXP_BeginSprites();
void MYXP_EndSprites();

void MYXP_AdvanceSprite(const void** data, byte count);

#endif
