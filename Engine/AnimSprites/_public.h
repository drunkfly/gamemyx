/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_ANIMSPRITES_PUBLIC_H
#define ENGINE_ANIMSPRITES_PUBLIC_H
#if ENABLE_ANIMATED_SPRITES

typedef byte MYXAnimSprite;

MYXAnimSprite MYX_CreateAnimSprite(
    const void* data, byte count, byte delay, byte paletteIndex);

MYXAnimSprite MYX_LoadAnimSprite(const void** data);

void MYX_SetAnimSpritePlayOnce(MYXAnimSprite sprite);
void MYX_PutAnimSprite(int x, int y, MYXAnimSprite sprite);
void MYX_PutAnimSpriteEx(int x, int y, MYXAnimSprite sprite, byte flags);

#endif
#endif
