/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_ANIMSPRITES_PUBLIC_H
#define ENGINE_ANIMSPRITES_PUBLIC_H

typedef byte MYXAnimSprite;

MYXAnimSprite MYX_CreateAnimSprite(
    const void* data, byte count, byte delay, byte paletteIndex);

void MYX_PutAnimSprite(int x, byte y, MYXAnimSprite sprite);

#endif
