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

void MYX_StartQuest(Quest* quest)
{
    ASSERT(quest->state == QUEST_NOT_STARTED);

    quest->state = QUEST_ACTIVE;

    quest->next = MYXP_ActiveQuests;
    MYXP_ActiveQuests = quest;

    strcpy(buf, "Quest received:\n");
    strcat(buf, quest->title);
    MYX_DisplayNotification(buf);
}

#endif
