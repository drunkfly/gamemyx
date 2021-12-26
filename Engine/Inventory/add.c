/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INVENTORY
#pragma constseg MYX_INVENTORY
#endif

void MYX_AddInventory(ITEM* item, byte count)
{
    if (count == 0)
        return;

    if (item->count != 0) {
        item->count += count;
        return;
    }

    item->count += count;

    item->next = MYXP_Inventory;
    MYXP_Inventory = item;
}
