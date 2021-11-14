/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_COLLISION

#ifdef __SDCC
#pragma codeseg MYX_COLLISIONS
#pragma constseg MYX_COLLISIONS
#endif

void MYX_SetCollisionCallback(byte tag, MYXCOLLISIONCALLBACK callback)
{
    MYXP_Callbacks[tag] = callback;
}

#endif
