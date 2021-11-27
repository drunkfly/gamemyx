/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <string.h>
#include "../config.h"

#define STRUCT(X) \
    struct X; \
    typedef struct X X; \
    struct X

#ifdef TARGET_ZXNEXT
 #if 1//def NDEBUG
  #define ASSERT(X) ((void)0)
  #define ASSERT_BANK(NUM) ((void)0)
 #else
  #define ASSERT(X) \
    ((X) ? (void)0 : MYX_AssertFailed(__FILE__, __LINE__, #X))
  #define ASSERT_BANK(NUM)
 #endif
#else
 #include <assert.h>
 #define ASSERT(X) assert(X)
#endif

#ifdef TARGET_ZXNEXT
 #define Z88DK_FASTCALL __z88dk_fastcall
 #define Z88DK_PRESERVES(REGS) __preserves_regs REGS
#else
 #define Z88DK_FASTCALL
 #define Z88DK_PRESERVES(REGS)
#endif

typedef unsigned char byte;
typedef unsigned short word;

/* should be declared in game code. */
void GameMain();

#include "AnimSprites/_public.h"
#include "Collisions/_public.h"
#include "Core/_public.h"
#include "Input/_public.h"
#include "Maps/_public.h"
#include "Render/_public.h"
#include "Text/_public.h"

#endif
