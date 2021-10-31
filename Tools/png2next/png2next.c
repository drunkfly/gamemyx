#include <stdio.h>
#include "engine.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#include "stb_image.h"

#define CHECK_ARG \
    if (i == argc - 1) { \
        fprintf(stderr, "error: missing command line argument after \"%s\".\n", argv[i]); \
        return 1; \
    }

struct HistogramEntry
{
    unsigned char index;
    unsigned char count;
};

static stbi_uc* image;
static int imageWidth;
static int imageHeight;
static int areaX;
static int areaY;
static int areaW;
static int areaH;

static unsigned char palette4[16];
static struct HistogramEntry histogram[256];

static void unloadFile()
{
    if (image != NULL) {
        stbi_image_free(image);
        image = NULL;
    }
}

static void loadFile(const char* file)
{
    unloadFile();

    image = stbi_load(file, &imageWidth, &imageHeight, NULL, 4);
    if (!image) {
        fprintf(stderr, "error: can't load \"%s\": %s\n", file, stbi_failure_reason());
        exit(1);
    }

    areaX = 0;
    areaY = 0;
    areaW = imageWidth;
    areaH = imageHeight;
}

static void buildHistogram()
{
    for (int y = 0; y < areaH; y++) {
        for (int x = 0; x < areaW; x++) {
            unsigned char r = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 0];
            unsigned char g = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 1];
            unsigned char b = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 2];
            unsigned char a = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 3];

            if (a < 128)
                continue; // skip transparent color

            unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);
            histogram[c].count++;
        }
    }
}

static int histogramSort(const void* p1, const void* p2)
{
    struct HistogramEntry* e1 = (struct HistogramEntry*)p1;
    struct HistogramEntry* e2 = (struct HistogramEntry*)p2;
    if (e1->count > e2->count)
        return -1;
    else if (e1->count < e2->count)
        return 1;
    return 0;
}

static void makePalette4()
{
    struct HistogramEntry sortedHistogram[256];
    memcpy(sortedHistogram, histogram, sizeof(struct HistogramEntry) * 256);
    qsort(sortedHistogram, 256, sizeof(struct HistogramEntry), histogramSort);

    int paletteIndex = 0;
    for (int i = 0; i < 15; i++) {
        if (paletteIndex == TRANSPARENT_COLOR_INDEX4)
            ++paletteIndex;
        palette4[i] = sortedHistogram[i].index;
    }
}

static void outputPalette4(const char* file)
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

static void output4Bit(const char* file)
{
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    fprintf(f, "SPRITE_FLAG_16COLOR,\n");

    for (int y = 0; y < areaH; y++) {
        unsigned char pixel = 0;
        for (int x = 0; x < areaW; x++) {
            unsigned char r = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 0];
            unsigned char g = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 1];
            unsigned char b = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 2];
            unsigned char a = image[((areaY + y) * imageWidth + (areaX + x)) * 4 + 3];

            if (a < 128) {
                if (x % 2 == 0)
                    pixel = TRANSPARENT_COLOR_INDEX4;
                else {
                    pixel |= (TRANSPARENT_COLOR_INDEX4 << 4);
                    fprintf(f, "0x%02X,", pixel);
                }
                continue;
            }

            unsigned char c = (b >> 6) | ((g >> 3) & 0x1c) | (r & 0xe0);

            signed char paletteIndex = -1;
            for (int i = 0; i < 16; i++) {
                if (i == TRANSPARENT_COLOR_INDEX4)
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
                    if (i == TRANSPARENT_COLOR_INDEX4)
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
                pixel = paletteIndex;
            else {
                pixel |= (paletteIndex << 4);
                fprintf(f, "0x%02X,", pixel);
            }
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int main(int argc, char** argv)
{
    atexit(unloadFile);

    for (int i = 0; i < 256; i++)
        histogram[i].index = i;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-in")) {
            CHECK_ARG
            loadFile(argv[++i]);
        } else if (!strcmp(argv[i], "-area16x16")) {
            CHECK_ARG
            int x = atoi(argv[++i]);
            CHECK_ARG
            int y = atoi(argv[++i]);
            areaX = x * 16;
            areaY = y * 16;
            areaW = 16;
            areaH = 16;
        } else if (!strcmp(argv[i], "-histogram")) {
            CHECK_ARG
            buildHistogram();
        } else if (!strcmp(argv[i], "-palette4")) {
            CHECK_ARG
            makePalette4();
        } else if (!strcmp(argv[i], "-outpalette4")) {
            CHECK_ARG
            outputPalette4(argv[++i]);
        } else if (!strcmp(argv[i], "-out4")) {
            CHECK_ARG
            output4Bit(argv[++i]);
        } else {
            fprintf(stderr, "error: unknown command line argument \"%s\".\n", argv[i]);
            return 1;
        }
    }
}
