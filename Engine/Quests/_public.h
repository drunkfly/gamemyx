/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_QUESTS_PUBLIC_H
#define ENGINE_QUESTS_PUBLIC_H
#if ENABLE_QUESTS

enum QuestState
{
    QUEST_NOT_STARTED,
    QUEST_ACTIVE,
    QUEST_COMPLETED,
    QUEST_FAILED,
};

STRUCT(Quest);
typedef void (*MYX_PFNUPDATEQUESTPROC)(Quest* quest);

struct Quest
{
    const char* title;
    MYX_PFNUPDATEQUESTPROC updateProc;
    byte state;
    Quest* next;
};

void MYX_StartQuest(Quest* quest);
void MYX_CompleteQuest(Quest* quest);

#endif
#endif
