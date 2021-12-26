/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INVENTORY
#pragma constseg MYX_INVENTORY
#endif

bool MYX_RemoveInventory(ITEM* item, byte count)
{
    ASSERT(count != 0);

    if (count > item->count)
        return false;

    item->count -= count;

    if (item->count == 0) {
        ITEM** p = &MYXP_Inventory;
        while (*p != item) {
            ASSERT(*p != NULL);
            p = &(*p)->next;
        }

        *p = item->next;
        item->next = NULL;
    }

    return true;
}
