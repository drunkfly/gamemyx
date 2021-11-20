/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_CORE_PRIVATE_H
#define ENGINE_CORE_PRIVATE_H

#ifdef TARGET_SDL2
#include "SDL2/common.h"
#elif defined(TARGET_ZXNEXT)
#include "ZXNext/zxnext.h"
#endif

extern byte MYXP_CurrentBank;

void MYXP_PlatformInit();
void MYXP_EngineMain();

void MYXP_SetUpperMemoryBank(byte bank);

void MYXP_WaitVSync();

#endif
