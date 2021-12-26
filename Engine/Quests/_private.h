/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_QUESTS_PRIVATE_H
#define ENGINE_QUESTS_PRIVATE_H
#if ENABLE_QUESTS

extern Quest* MYXP_ActiveQuests;
extern Quest* MYXP_CompletedQuests;

void MYXP_UpdateQuests();

#endif
#endif
