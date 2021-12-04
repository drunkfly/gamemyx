/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine_p.h"

char* MYX_ByteToString(char* buffer, byte value)
{
    char* p = buffer;
    *p++ = (value / 100) + '0';     value %= 100;
    *p++ = (value / 10) + '0';      value %= 10;
    *p++ = value + '0';

    p = buffer;
    if (*p == '0') ++p;
    if (*p == '0') ++p;

    return p;
}

char* MYX_WordToString(char* buffer, word value)
{
    char* p = buffer;
    *p++ = (value / 10000) + '0';   value %= 10000;
    *p++ = (value / 1000) + '0';    value %= 1000;
    *p++ = (value / 100) + '0';     value %= 100;
    *p++ = (value / 10) + '0';      value %= 10;
    *p++ = value + '0';

    p = buffer;
    if (*p == '0') ++p;
    if (*p == '0') ++p;
    if (*p == '0') ++p;
    if (*p == '0') ++p;

    return p;
}
