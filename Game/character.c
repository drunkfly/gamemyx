/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "character.h"

void Character_Init(Character* c, int x, int y, const void* sprites)
{
    c->state = CHAR_IDLE;
    c->direction = DIR_DOWN;
    c->x = x;
    c->y = y;
    c->timer = 0;

    for (byte dir = 0; dir < 4; dir++) {
        c->idle[dir] = MYX_LoadAnimSprite(&sprites);
        c->walk[dir] = MYX_LoadAnimSprite(&sprites);
    }    

    c->death = MYX_LoadAnimSprite(&sprites);
    MYX_SetAnimSpritePlayOnce(c->death);
}

void Character_Draw(Character* c)
{
    switch (c->state) {
        case CHAR_IDLE:
            MYX_PutAnimSprite(c->x, c->y, c->idle[c->direction]);
            break;
        case CHAR_WALK:
            c->state = CHAR_IDLE;
            MYX_PutAnimSprite(c->x, c->y, c->walk[c->direction]);
            break;
        case CHAR_DEAD:
            if (c->timer < 32) {
                MYX_PutAnimSprite(c->x, c->y, c->death);
                ++(c->timer);
            }
            break;
    }
}

void Character_Kill(Character* c)
{
    if (c->state == CHAR_DEAD)
        return;

    c->state = CHAR_DEAD;
    c->timer = 0;
}

bool Character_MoveLeft(Character* c)
{
    if (c->state == CHAR_DEAD)
        return false;

    c->state = CHAR_WALK;
    c->direction = DIR_LEFT;

    if (c->x > 0) {
        --(c->x);
        if (!MYX_CollidesWithMap16x16(c->x, c->y))
            return true;
        ++(c->x);
    }

    return false;
}

bool Character_MoveRight(Character* c)
{
    if (c->state == CHAR_DEAD)
        return false;

    c->state = CHAR_WALK;
    c->direction = DIR_RIGHT;

    if (c->x < MYX_MapWidth-16) {
        ++(c->x);
        if (!MYX_CollidesWithMap16x16(c->x, c->y))
            return true;
        --(c->x);
    }

    return false;
}

bool Character_MoveUp(Character* c)
{
    if (c->state == CHAR_DEAD)
        return false;

    c->state = CHAR_WALK;
    c->direction = DIR_UP;

    if (c->y > 0) {
        --(c->y);
        if (!MYX_CollidesWithMap16x16(c->x, c->y))
            return true;
        ++(c->y);
    }

    return false;
}

bool Character_MoveDown(Character* c)
{
    if (c->state == CHAR_DEAD)
        return false;

    c->state = CHAR_WALK;
    c->direction = DIR_DOWN;

    if (c->y < MYX_MapHeight-16) {
        ++(c->y);
        if (!MYX_CollidesWithMap16x16(c->x, c->y))
            return true;
        --(c->y);
    }

    return false;
}

void Character_HandleInput(Character* c)
{
    if (c->state == CHAR_DEAD)
        return;

    if (MYX_IsKeyPressed(KEY_O) || MYX_IsGamepad1Pressed(GAMEPAD_LEFT))
        Character_MoveLeft(c);

    if (MYX_IsKeyPressed(KEY_P) || MYX_IsGamepad1Pressed(GAMEPAD_RIGHT))
        Character_MoveRight(c);

    if (MYX_IsKeyPressed(KEY_Q) || MYX_IsGamepad1Pressed(GAMEPAD_UP))
        Character_MoveUp(c);

    if (MYX_IsKeyPressed(KEY_A) || MYX_IsGamepad1Pressed(GAMEPAD_DOWN))
        Character_MoveDown(c);
}

void Character_ForwardBackwardMove(Character* c)
{
    if (c->state == CHAR_DEAD)
        return;

    (c->timer)++;
    if (c->timer < 4) {
        c->state = CHAR_WALK;
        return;
    }
    c->timer = 0;

    switch (c->direction) {
        case DIR_LEFT:
            if (!Character_MoveLeft(c))
                c->direction = DIR_RIGHT;
            break;
        case DIR_RIGHT:
            if (!Character_MoveRight(c))
                c->direction = DIR_LEFT;
            break;
        case DIR_UP:
            if (!Character_MoveUp(c))
                c->direction = DIR_DOWN;
            break;
        case DIR_DOWN:
            if (!Character_MoveDown(c))
                c->direction = DIR_UP;
            break;
    }
}
