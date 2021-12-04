/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_CORE_PUBLIC_H
#define ENGINE_CORE_PUBLIC_H

#if defined(ENABLE_ASSERTIONS) \
    && defined(TARGET_ZXNEXT) \
    && !defined(NDEBUG)
extern byte MYXP_CurrentBank;
#endif

void MYX_Cleanup();

void MYX_BeginFrame();
void MYX_EndFrame();

char* MYX_ByteToString(char* buffer, byte value);
char* MYX_WordToString(char* buffer, word value);

#endif
