#ifndef PLAYER_H
#define PLAYER_H

#include "engine.h"
#include "character.h"

extern Character player;
extern byte playerCurLives;

void GAME_InitPlayer(int px, int py);
void GAME_UpdatePlayer(void);
bool GAME_IsPlayerAlive(void);

#endif
