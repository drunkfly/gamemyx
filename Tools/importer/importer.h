/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#ifndef IMPORTER_H
#define IMPORTER_H

#include "engine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

STRUCT(HistogramEntry)
{
    unsigned char index;
    unsigned char count;
};

extern int imageWidth;
extern int imageHeight;
extern int imageAreaX;
extern int imageAreaY;
extern int imageAreaW;
extern int imageAreaH;

extern unsigned char palette4[16];
extern HistogramEntry histogram[256];

void unloadImage();
void loadImage(const char* file);
void buildImageHistogram();
void makeImagePalette4();
void outputImagePalette4(const char* file);
void output4BitImage(const char* file);

#endif
