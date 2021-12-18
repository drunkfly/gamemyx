/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

#ifdef __SDCC
#pragma codeseg MYX_QUESTS
#pragma constseg MYX_QUESTS
#endif

Quest* MYXP_ActiveQuests;
Quest* MYXP_CompletedQuests;

void MYXP_UpdateQuests()
{
    for (Quest* p = MYXP_ActiveQuests; p; p = p->next) {
        if (p->updateProc)
            p->updateProc(p);
    }
}
