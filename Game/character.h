/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "engine.h"

#define MAX_ENEMIES 16
#define MAX_NPCS 16

enum State
{
    CHAR_IDLE,
    CHAR_WALK,
    CHAR_MELEE_ATTACK,
    CHAR_DEAD,
};

enum
{
    TAG_PLAYER,
    TAG_PLAYER_ATTACK,
    TAG_ENEMY,                              // + N
    TAG_NPC = TAG_ENEMY + MAX_ENEMIES,      // + N
    TAG_COG = TAG_NPC + MAX_NPCS,            // + N
};

#define REF_SPRITE          0x40
#define NO_SPRITE           0x80

STRUCT(Character)
{
    MYXAnimSprite idle[4];
    MYXAnimSprite walk[4];
    MYXAnimSprite meleeAttack[4];
    MYXAnimSprite death[4];
    byte idleFlags[4];
    byte walkFlags[4];
    byte meleeAttackFlags[4];
    byte deathFlags[4];
    int x;
    int y;
    byte collisionX;
    byte collisionY;
    byte collisionW;
    byte collisionH;
    byte direction;
    byte state;
    byte timer;
    byte tag;
    byte attackTag;
};

void Character_Init(Character* c, int x, int y, byte tag, const void* sprites);
void Character_Copy(Character* c, const Character* src, int x, int y);

bool Character_FinishedDying(Character* c);

void Character_Draw(Character* c);

void Character_Kill(Character* c);

bool Character_MoveLeft(Character* c);
bool Character_MoveRight(Character* c);
bool Character_MoveUp(Character* c);
bool Character_MoveDown(Character* c);

bool Character_MeleeAttack(Character* c);

void Character_ForwardBackwardMove(Character* c);

bool Character_HandleInput(Character* c);

#endif
