/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_INVENTORY
#pragma constseg MYX_INVENTORY
#endif

void MYX_ClearInventory()
{
    for (ITEM* p = MYXP_Inventory; p; ++p) {
        p->count = 0;
        p->next = NULL;
    }

    MYXP_Inventory = NULL;
}
