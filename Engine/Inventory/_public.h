/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_INVENTORY_PUBLIC_H
#define ENGINE_INVENTORY_PUBLIC_H
#if ENABLE_INVENTORY

STRUCT(ITEM)
{
    const char* name;
    const void* imageData;
    byte imageBank;
    byte count;
    ITEM* next;
};

void MYX_ClearInventory();
void MYX_AddInventory(ITEM* item, byte count);
bool MYX_RemoveInventory(ITEM* item, byte count);
ITEM* MYX_GetInventory();
byte MYX_GetInventoryCount(const ITEM* item);

#endif
#endif
