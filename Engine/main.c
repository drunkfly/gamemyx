/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

void MYXP_EngineMain()
{
    MYXP_PlatformInit();

    GameMain();

    for (;;) {}
}
