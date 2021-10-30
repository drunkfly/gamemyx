/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "engine.h"
#include <stdio.h>

int count;

void InterruptHandler()
{
    printf("%d\n", count++);
}
