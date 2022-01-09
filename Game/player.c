#include "player.h"
#include "Data/data.h"

Character player;
byte playerCurLives;
static byte playerInvincible;

void GAME_InitPlayer(int px, int py)
{
    Character_Init(&player, px, py, TAG_PLAYER, SwordsmanData);
    player.attackTag = TAG_PLAYER_ATTACK;
}

void GAME_UpdatePlayer(void)
{
    if (playerInvincible == 0)
        Character_Draw(&player);
    else {
        --playerInvincible;
        if ((playerInvincible & 15) < 8)
            Character_Draw(&player);
    }

    Character_HandleInput(&player);

    MYX_SetMapVisibleCenter(player.x, player.y);
}

bool GAME_IsPlayerAlive(void)
{
    return playerCurLives != 0 || !Character_FinishedDying(&player);
}
