/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "engine.h"

enum Direction
{
    DIR_LEFT = 0,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN,
};

enum State
{
    CHAR_IDLE,
    CHAR_WALK,
    CHAR_DEAD,
};

STRUCT(Character)
{
    MYXAnimSprite idle[4];
    MYXAnimSprite walk[4];
    MYXAnimSprite death;
    int x;
    int y;
    byte direction;
    byte state;
    byte timer;
};

void Character_Init(Character* c, int x, int y, const void* sprites);

void Character_Draw(Character* c);

void Character_Kill(Character* c);

bool Character_MoveLeft(Character* c);
bool Character_MoveRight(Character* c);
bool Character_MoveUp(Character* c);
bool Character_MoveDown(Character* c);

void Character_ForwardBackwardMove(Character* c);

bool Character_HandleInput(Character* c);

#endif
