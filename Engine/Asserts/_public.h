/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef ENGINE_ASSERTS_PUBLIC_H
#define ENGINE_ASSERTS_PUBLIC_H
#if ENABLE_ASSERTIONS

#ifdef TARGET_ZXNEXT
 #ifdef NDEBUG
  #define ASSERT(X) ((void)0)
  #define ASSERT_NEXT_BANK(NUM) ((void)0)
 #else
  #define ASSERT(X) \
    ((X) \
        ? (void)0 \
        : MYX_AssertFailed(__FILE__, __LINE__, #X))
  #define ASSERT_NEXT_BANK(NUM) \
    ((MYXP_CurrentBank == (NUM)) \
        ? (void)0 \
        : MYX_AssertBankFailed(__FILE__, __LINE__, NUM))
 #endif
#else
 #include <assert.h>
 #define ASSERT(X) assert(X)
 #define ASSERT_NEXT_BANK(NUM) ((void)0)
#endif

#define MYX_ASSERT_BACKGROUND_COLOR     0xC0
#define MYX_ASSERT_TEXT_COLOR           0xFF

void MYX_AssertFailed(const char* file, word line, const char* expr);
void MYX_AssertBankFailed(const char* file, word line, byte bank);

#endif
#endif
