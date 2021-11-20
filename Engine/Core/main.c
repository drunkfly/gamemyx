/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_CORE
#pragma constseg MYX_CORE
#endif

void MYXP_EngineMain()
{
    MYXP_PlatformInit();

  #ifdef TARGET_ZXNEXT
    MYXP_SetUpperMemoryBank(1);
  #endif

    GameMain();

    for (;;) {}
}
