/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_CORE_PRIVATE_H
#define ENGINE_CORE_PRIVATE_H

#ifdef ZXNEXT
#include "ZXNext/zxnext.h"
#endif

extern byte MYXP_CurrentBank;

void MYXP_PlatformInit();

void MYXP_SetUpperMemoryBank(byte bank);

#endif
