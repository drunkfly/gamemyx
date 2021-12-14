/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_MUSIC_PUBLIC_H
#define ENGINE_MUSIC_PUBLIC_H
#if ENABLE_MUSIC

#define MYX_AY_CHIP1    1
#define MYX_AY_CHIP2    2
#define MYX_AY_CHIP3    4
#define MYX_AY_ALL      (MYX_AY_CHIP1 | MYX_AY_CHIP2 | MYX_AY_CHIP3)

void MYX_StopMusic(byte ayMask) Z88DK_FASTCALL;
void MYX_PlayMusic(byte ayMask) Z88DK_FASTCALL;

void MYX_SetMusic(byte ay, const void* data, byte bank);

#endif
#endif
