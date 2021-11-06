/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_COLLISION

void MYX_SetCollisionCallback(byte tag, MYXCOLLISIONCALLBACK callback)
{
    MYXP_Callbacks[tag] = callback;
}

#endif
