/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INVENTORY
#pragma constseg MYX_INVENTORY
#endif

byte MYX_GetInventoryCount(const ITEM* item)
{
    return item->count;
}
