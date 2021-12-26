/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "character.h"

#define DEATH_TIME 32

static void LoadSprites(const byte **p,
    MYXAnimSprite* outSprites, byte* outFlags, byte* outMirror)
{
    for (byte dir = 0; dir < 4; dir++) {
        byte flags = *(*p)++;
        outFlags[dir] = flags;
        if ((flags & NO_SPRITE) == 0) {
            if ((flags & REF_SPRITE) == 0)
                outSprites[dir] = MYX_LoadAnimSprite(p);
            else {
                ASSERT(**p < 4);
                outMirror[dir] = *(*p)++;
            }
        }
    }
}

void Character_Init(Character* c, int x, int y, byte tag, const void* sprites)
{
    const byte* p = (const byte*)sprites;

    c->state = CHAR_IDLE;
    c->direction = DIR_DOWN;
    c->x = x;
    c->y = y;
    c->timer = 0;
    c->tag = c->attackTag = tag;
    c->collisionX = 3;
    c->collisionY = 3;
    c->collisionW = 16 - 6;
    c->collisionH = 16 - 6;

    byte mirrorIdleSource[4] = { 0, 0, 0, 0 };
    byte mirrorWalkSource[4] = { 0, 0, 0, 0 };
    byte mirrorMeleeSource[4] = { 0, 0, 0, 0 };
    byte mirrorDeathSource[4] = { 0, 0, 0, 0 };

    LoadSprites(&p, c->idle, c->idleFlags, mirrorIdleSource);
    LoadSprites(&p, c->walk, c->walkFlags, mirrorWalkSource);
    LoadSprites(&p, c->meleeAttack, c->meleeAttackFlags, mirrorMeleeSource);
    LoadSprites(&p, c->death, c->deathFlags, mirrorDeathSource);

    for (byte dir = 0; dir < 4; dir++) {
        if (c->idleFlags[dir] & REF_SPRITE)
            c->idle[dir] = c->idle[mirrorIdleSource[dir]];
        c->idleFlags[dir] &= MYX_FLIP_X | MYX_FLIP_Y;

        if (c->walkFlags[dir] & REF_SPRITE)
            c->walk[dir] = c->walk[mirrorWalkSource[dir]];
        c->walkFlags[dir] &= MYX_FLIP_X | MYX_FLIP_Y;

        if (c->meleeAttackFlags[dir] & REF_SPRITE)
            c->meleeAttack[dir] = c->meleeAttack[mirrorMeleeSource[dir]];
        c->meleeAttackFlags[dir] &= MYX_FLIP_X | MYX_FLIP_Y;

        if (c->deathFlags[dir] & REF_SPRITE)
            c->death[dir] = c->death[mirrorDeathSource[dir]];
        c->deathFlags[dir] &= MYX_FLIP_X | MYX_FLIP_Y;
    }
}

void Character_Copy(Character* c, const Character* src, int x, int y)
{
    c->state = CHAR_IDLE;
    c->direction = DIR_DOWN;
    c->x = x;
    c->y = y;
    c->timer = 0;
    c->tag = src->tag;
    c->collisionX = src->collisionX;
    c->collisionY = src->collisionY;
    c->collisionW = src->collisionW;
    c->collisionH = src->collisionH;

    for (byte dir = 0; dir < 4; dir++) {
        c->idle[dir] = src->idle[dir];
        c->idleFlags[dir] = src->idleFlags[dir];
        c->walk[dir] = src->walk[dir];
        c->walkFlags[dir] = src->walkFlags[dir];
        c->meleeAttack[dir] = src->meleeAttack[dir];
        c->meleeAttackFlags[dir] = src->meleeAttackFlags[dir];
        c->death[dir] = src->death[dir];
        c->deathFlags[dir] = src->deathFlags[dir];
    }
}

static void AddCollision(Character* c)
{
    MYX_AddCollision(c->x + c->collisionX, c->y + c->collisionY,
        c->collisionW, c->collisionH, c->tag);
}

bool Character_FinishedDying(Character* c)
{
    return (c->state == CHAR_DEAD && c->timer >= DEATH_TIME);
}

void Character_Draw(Character* c)
{
    switch (c->state) {
        case CHAR_IDLE:
            AddCollision(c);
            MYX_PutAnimSpriteEx(c->x, c->y,
                c->idle[c->direction], c->idleFlags[c->direction]);
            break;
        case CHAR_WALK:
            c->state = CHAR_IDLE;
            AddCollision(c);
            MYX_PutAnimSpriteEx(c->x, c->y,
                c->walk[c->direction], c->idleFlags[c->direction]);
            break;
        case CHAR_DEAD:
            if (c->timer < DEATH_TIME) {
                MYX_PutAnimSpriteEx(c->x, c->y,
                    c->death[c->direction], c->deathFlags[c->direction]);
                ++(c->timer);
            }
            break;
        case CHAR_MELEE_ATTACK:
            AddCollision(c);
            if (c->timer < 32) {
                MYX_PutAnimSpriteEx(c->x, c->y,
                    c->meleeAttack[c->direction],
                    c->meleeAttackFlags[c->direction]);

                if (c->timer > 8 && c->timer < 24) { // FIXME: hardcoded
                    int x, y;
                    byte w, h;
                    switch (c->direction) {
                        case DIR_LEFT:
                            x = c->x - 8; // FIXME: hardcoded
                            y = c->y;
                            w = 8;
                            h = 16;
                            break;
                        case DIR_RIGHT:
                            x = c->x + 16; // FIXME: hardcoded
                            y = c->y;
                            w = 8;
                            h = 16;
                            break;
                        case DIR_UP:
                            x = c->x;
                            y = c->y - 8; // FIXME: hardcoded
                            w = 16;
                            h = 8;
                            break;
                        case DIR_DOWN:
                            x = c->x;
                            y = c->y + 16; // FIXME: hardcoded
                            w = 16;
                            h = 8;
                            break;
                    }

                    MYX_AddCollision(x, y, w, h, c->attackTag);
                }

                ++(c->timer);
                if (c->timer == 32) { // FIXME: hardcoded
                    c->state = CHAR_IDLE;
                    c->timer = 0;
                }
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
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
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
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
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
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
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
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
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

bool Character_MeleeAttack(Character* c)
{
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
        return false;

    c->state = CHAR_MELEE_ATTACK;
    c->timer = 0;

    return true;
}

bool Character_HandleInput(Character* c)
{
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
        return false;

    bool result = false;

    if (MYX_IsKeyPressed(KEY_O) || MYX_IsGamepad1Pressed(GAMEPAD_LEFT))
        result |= Character_MoveLeft(c);

    if (MYX_IsKeyPressed(KEY_P) || MYX_IsGamepad1Pressed(GAMEPAD_RIGHT))
        result |= Character_MoveRight(c);

    if (MYX_IsKeyPressed(KEY_Q) || MYX_IsGamepad1Pressed(GAMEPAD_UP))
        result |= Character_MoveUp(c);

    if (MYX_IsKeyPressed(KEY_A) || MYX_IsGamepad1Pressed(GAMEPAD_DOWN))
        result |= Character_MoveDown(c);

    if (MYX_IsKeyPressed(KEY_SPACE) || MYX_IsGamepad1Pressed(GAMEPAD_A))
        result |= Character_MeleeAttack(c);

    return result;
}

void Character_ForwardBackwardMove(Character* c)
{
    if (c->state == CHAR_DEAD || c->state == CHAR_MELEE_ATTACK)
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
