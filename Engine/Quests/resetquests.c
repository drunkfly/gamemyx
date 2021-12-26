/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"
#if ENABLE_QUESTS

#ifdef __SDCC
#pragma codeseg MYX_QUESTS
#pragma constseg MYX_QUESTS
#endif

static char buf[128]; // FIXME

void MYX_ResetQuests()
{
    Quest* p;

    for (p = MYXP_ActiveQuests; p; p = p->next) {
        ASSERT(p->state == QUEST_ACTIVE);
        p->state = QUEST_NOT_STARTED;
        p->next = NULL;
    }

    for (p = MYXP_CompletedQuests; p; p = p->next) {
        ASSERT(p->state == QUEST_COMPLETED);
        p->state = QUEST_NOT_STARTED;
        p->next = NULL;
    }

    MYXP_ActiveQuests = NULL;
    MYXP_CompletedQuests = NULL;
}

#endif
