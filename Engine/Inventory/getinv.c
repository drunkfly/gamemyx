/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INVENTORY
#pragma constseg MYX_INVENTORY
#endif

ITEM* MYX_GetInventory()
{
    return MYXP_Inventory;
}
