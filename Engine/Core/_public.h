/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_CORE_PUBLIC_H
#define ENGINE_CORE_PUBLIC_H

typedef enum Direction {
    DIR_LEFT = 0,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
    DIR_UP_LEFT,
    DIR_UP_RIGHT,
    DIR_DOWN_LEFT,
    DIR_DOWN_RIGHT,
} Direction;

#if defined(ENABLE_ASSERTIONS) \
    && defined(TARGET_ZXNEXT) \
    && !defined(NDEBUG)
extern byte MYXP_CurrentUpperBank;
extern byte MYXP_CurrentLowerBank;
#endif

typedef void (*MYX_PFNHUDPROC)();

void MYX_Cleanup();

void MYX_BeginFrame();
void MYX_EndFrame();

void MYX_ResetHUD();
void MYX_RegisterHUD(MYX_PFNHUDPROC proc) Z88DK_FASTCALL;
void MYX_DrawHUD();

char* MYX_ByteToString(char* buffer, byte value);
char* MYX_WordToString(char* buffer, word value);

#endif
