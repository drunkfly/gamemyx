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

void MYX_CompleteQuest(Quest* quest)
{
    ASSERT(quest->state == QUEST_ACTIVE);

    quest->state = QUEST_COMPLETED;

    // Remove from list of active quests
    Quest** p = &MYXP_ActiveQuests;
    while (*p) {
        if (*p == quest) {
            *p = quest->next;
            break;
        }
        p = &quest->next;
    }

    // Add to list of completed quests
    quest->next = MYXP_CompletedQuests;
    MYXP_CompletedQuests = quest;

    strcpy(buf, "Quest completed:\n");
    strcat(buf, quest->title);
    MYX_DisplayNotification(buf);
}

#endif
