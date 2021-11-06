/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#include "stb_image.h"

static stbi_uc* image;

int imageWidth;
int imageHeight;
int imageAreaX;
int imageAreaY;
int imageAreaW;
int imageAreaH;

unsigned char palette4[16];
HistogramEntry histogram[256];

void unloadImage()
{
    if (image != NULL) {
        stbi_image_free(image);
        image = NULL;
    }
}

void loadImage(const char* file)
{
    unloadImage();

    image = stbi_load(file, &imageWidth, &imageHeight, NULL, 4);
    if (!image) {
        fprintf(stderr, "error: can't load \"%s\": %s\n", file, stbi_failure_reason());
        exit(1);
    }

    imageAreaX = 0;
    imageAreaY = 0;
    imageAreaW = imageWidth;
    imageAreaH = imageHeight;
}

void buildImageHistogram()
{
    for (int i = 0; i < 256; i++) {
        histogram[i].index = i;
        histogram[i].count = 0;
    }

    for (int y = 0; y < imageAreaH; y++) {
        for (int x = 0; x < imageAreaW; x++) {
            unsigned char r = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 0];
            unsigned char g = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 1];
            unsigned char b = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 2];
            unsigned char a = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 3];

            if (a < 128)
                continue; // skip transparent color

            unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);
            histogram[c].count++;
        }
    }
}

int histogramSort(const void* p1, const void* p2)
{
    HistogramEntry* e1 = (HistogramEntry*)p1;
    HistogramEntry* e2 = (HistogramEntry*)p2;
    if (e1->count > e2->count)
        return -1;
    else if (e1->count < e2->count)
        return 1;
    return 0;
}

void makeImagePalette4()
{
    HistogramEntry sortedHistogram[256];
    memcpy(sortedHistogram, histogram, sizeof(HistogramEntry) * 256);
    qsort(sortedHistogram, 256, sizeof(HistogramEntry), histogramSort);

    int paletteIndex = 0;
    for (int i = 0; i < 15; i++) {
        if (paletteIndex == MYX_TRANSPARENT_COLOR_INDEX4)
            ++paletteIndex;
        palette4[i] = sortedHistogram[i].index;
    }
}

void outputImagePalette4(const char* file)
{
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    for (int i = 0; i < 16; i++)
        fprintf(f, "0x%02X,\n", palette4[i]);

    fclose(f);
}

void output4BitImage(const char* file)
{
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    fprintf(f, "MYX_SPRITE_FLAG_16COLOR,\n");

    for (int y = 0; y < imageAreaH; y++) {
        unsigned char pixel = 0;
        for (int x = 0; x < imageAreaW; x++) {
            unsigned char r = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 0];
            unsigned char g = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 1];
            unsigned char b = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 2];
            unsigned char a = image[((imageAreaY + y) * imageWidth + (imageAreaX + x)) * 4 + 3];

            if (a < 128) {
                if (x % 2 == 0)
                    pixel = (MYX_TRANSPARENT_COLOR_INDEX4 << 4);
                else {
                    pixel |= MYX_TRANSPARENT_COLOR_INDEX4;
                    fprintf(f, "0x%02X,", pixel);
                }
                continue;
            }

            unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);

            signed char paletteIndex = -1;
            for (int i = 0; i < 16; i++) {
                if (i == MYX_TRANSPARENT_COLOR_INDEX4)
                    continue;
                if (palette4[i] == c) {
                    paletteIndex = i;
                    break;
                }
            }

            if (paletteIndex < 0) {
                r >>= 5;
                g >>= 5;
                b >>= 6;

                int nearestDistance;
                for (int i = 0; i < 16; i++) {
                    if (i == MYX_TRANSPARENT_COLOR_INDEX4)
                        continue;
                    
                    unsigned char pR = c >> 5;
                    unsigned char pG = (c >> 2) & 7;
                    unsigned char pB = c & 3;

                    int x = r - pR;
                    int y = g - pG;
                    int z = b - pB;
                    int distance = x * x + y * y + z * z;

                    if (paletteIndex < 0 || distance < nearestDistance) {
                        nearestDistance = distance;
                        paletteIndex = i;
                    }
                }
            }

            if (x % 2 == 0)
                pixel = (paletteIndex << 4);
            else {
                pixel |= paletteIndex;
                fprintf(f, "0x%02X,", pixel);
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}
