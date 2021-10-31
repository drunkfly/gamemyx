/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"

#define CHECK_ARG \
    if (i == argc - 1) { \
        fprintf(stderr, "error: missing command line argument after \"%s\".\n", argv[i]); \
        return 1; \
    }

int main(int argc, char** argv)
{
    atexit(unloadImage);
    atexit(unloadTilesets);
    atexit(unloadTilemap);

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-loadimage")) {
            CHECK_ARG
            loadImage(argv[++i]);
        } else if (!strcmp(argv[i], "-area16x16")) {
            CHECK_ARG
            int x = atoi(argv[++i]);
            CHECK_ARG
            int y = atoi(argv[++i]);
            imageAreaX = x * 16;
            imageAreaY = y * 16;
            imageAreaW = 16;
            imageAreaH = 16;
        } else if (!strcmp(argv[i], "-histogram")) {
            CHECK_ARG
            buildImageHistogram();
        } else if (!strcmp(argv[i], "-palette4")) {
            CHECK_ARG
            makeImagePalette4();
        } else if (!strcmp(argv[i], "-outpalette4")) {
            CHECK_ARG
            outputImagePalette4(argv[++i]);
        } else if (!strcmp(argv[i], "-outsprite4")) {
            CHECK_ARG
            output4BitImage(argv[++i]);
        } else if (!strcmp(argv[i], "-loadtsx")) {
            CHECK_ARG
            loadTileset(argv[++i]);
        } else if (!strcmp(argv[i], "-loadtmx")) {
            CHECK_ARG
            loadTilemap(argv[++i]);
        } else if (!strcmp(argv[i], "-outmap")) {
            CHECK_ARG
            outputTilemap(argv[++i]);
        } else if (!strcmp(argv[i], "-outtiles4")) {
            CHECK_ARG
            outputTileset4Bit(argv[++i]);
        } else {
            fprintf(stderr, "error: unknown command line argument \"%s\".\n", argv[i]);
            return 1;
        }
    }

    return 0;
}
