/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"
#include "stb_image.h"

#define MAX_CHARS 256

STRUCT(Char)
{
    FontChar fontChar;
    byte* image;
};

STRUCT(Image)
{
    stbi_uc* image;
    int width;
    int height;
};

static Image* images;
static int imageCount;

static Char chars[MAX_CHARS];
static int lineH;
static int baseline;

void unloadFont()
{
    for (int i = 0; i < MAX_CHARS; i++) {
        if (chars[i].image != NULL) {
            free(chars[i].image);
            chars[i].image = NULL;
        }
    }

    memset(chars, 0, sizeof(chars));

    if (images != NULL) {
        for (int i = 0; i < imageCount; i++)
            stbi_image_free(images[i].image);
        imageCount = 0;
        free(images);
        images = NULL;
    }
}

void loadFnt(const char* file)
{
    unloadFont();

    FILE* f = fopen(file, "r");
    if (!f) {
        fprintf(stderr, "can't open file %s: %s\n", file, strerror(errno));
        exit(1);
    }

    char face[64];
    int size;
    int bold;
    int italic;
    char charset[64];
    int unicode;
    int stretchH;
    int smooth;
    int aa;
    int paddingX, paddingY, paddingW, paddingH;
    int spacingX, spacingY;
    int outline;
    int scaleW;
    int scaleH;
    int pages;
    int packed;
    int alphaChnl;
    int redChnl;
    int greenChnl;
    int blueChnl;

    fscanf(f, "info face=%s size=%d bold=%d italic=%d charset=%s unicode=%d stretchH=%d smooth=%d aa=%d padding=%d,%d,%d,%d spacing=%d,%d outline=%d\n",
        face, &size, &bold, &italic, charset, &unicode, &stretchH,
        &smooth, &aa, &paddingX, &paddingY, &paddingW, &paddingH,
        &spacingX, &spacingY, &outline);

    fscanf(f, "common lineHeight=%d base=%d scaleW=%d scaleH=%d pages=%d packed=%d alphaChnl=%d redChnl=%d greenChnl=%d blueChnl=%d\n",
        &lineH, &baseline, &scaleW, &scaleH, &pages, &packed,
        &alphaChnl, &redChnl, &greenChnl, &blueChnl);

    images = (Image*)calloc(pages, sizeof(Image));
    if (!images) {
        fclose(f);
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }

    for (int i = 0; i < pages; i++) {
        int id;
        char page[256] = {0};
        fscanf(f, "page id=%d file=%s\n", &id, page);

        size_t len = strlen(page);
        if (page[0] == '"' && page[len - 1] == '"') {
            memmove(page, &page[1], len - 2);
            page[len - 2] = 0;
        }

        char path[1024];
        strcpy(path, file);

        char* index = strrchr(path, '/');
        char* index2 = strrchr(path, '\\');
        if (index2 && (!index && index2 > index))
            index = index2;
        if (index)
            index[1] = 0;
        else
            path[0] = 0;

        strcat(path, page);

        int width, height;
        stbi_uc* image = stbi_load(path, &width, &height, NULL, 4);
        if (!image) {
            fprintf(stderr, "error: can't load \"%s\": %s\n", file, stbi_failure_reason());
            fclose(f);
            exit(1);
        }

        images[i].image = image;
        images[i].width = width;
        images[i].height = height;
    }

    int numChars;
    fscanf(f, "chars count=%d\n", &numChars);

    int offset = 0;

    for (int i = 0; i < numChars; i++) {
        int id, imgX, imgY, width, height, xoff, yoff, xadv, page, chnl;
        fscanf(f, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d page=%d chnl=%d\n",
            &id, &imgX, &imgY, &width, &height, &xoff, &yoff, &xadv, &page, &chnl);

        if (id > 255)
            continue;

        width += xoff;
        int w = (width + 7) / 8; /* in bytes */

        chars[id].image = malloc(w * height);
        if (!chars[id].image) {
            fprintf(stderr, "out of memory!\n");
            fclose(f);
            exit(1);
        }

        int off = 0;
        for (int y = 0; y < height; y++) {
            byte b = 0;
            for (int x = 0; x < width; x++) {
                if (x != 0 && (x & 7) == 0) {
                    chars[id].image[off++] = b;
                    b = 0;
                }

                bool bitset = false;
                if (x >= xoff) {
                    int addr = ((imgY + y) * images[page].width + imgX + x) * 4;
                    byte alpha = images[page].image[addr + 3];
                    bitset = (alpha > 0x80);
                }

                if (bitset)
                    b |= (1 << (7 - (x & 7)));
            }
            chars[id].image[off++] = b;
        }

        chars[id].fontChar.offset = (word)offset;
        chars[id].fontChar.w = (byte)w;
        chars[id].fontChar.h = (byte)height;
        chars[id].fontChar.yoff = (byte)yoff;
        chars[id].fontChar.xadv = (byte)xadv;

        offset += w * height;
    }

    fclose(f);
}

void writeFontBytes(const char* file)
{
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    for (int i = 0; i < MAX_CHARS; i++) {
        if (chars[i].image != NULL) {
            int off = 0;
            if ((unsigned)i >= 32 && i != 127)
                fprintf(f, "// %d \"%c\"\n", i, (char)i);
            else
                fprintf(f, "// %d\n", i);

            for (int y = 0; y < chars[i].fontChar.yoff; y++) {
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "     ");

                fprintf(f, " // ");
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "........");

                fprintf(f, "\n");
            }

            for (int y = 0; y < chars[i].fontChar.h; y++) {
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "0x%02X,", chars[i].image[off + x]);

                fprintf(f, " // ");
                for (int x = 0; x < chars[i].fontChar.w; x++) {
                    for (int j = 0; j < 8; j++) {
                        byte b = chars[i].image[off + x];
                        char c = (b & (1 << (7 - j)) ? '#' : '.');
                        fprintf(f, "%c", c);
                    }
                }

                off += chars[i].fontChar.w;
                fprintf(f, "\n");
            }

            for (int y = chars[i].fontChar.yoff + chars[i].fontChar.h; y < lineH; y++) {
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "     ");

                fprintf(f, " // ");
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "........");

                fprintf(f, "\n");
            }
        }
    }

    fclose(f);
}

void writeFontDef(const char* file)
{
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    fprintf(f, "%d, /* lineH */\n", lineH);
    fprintf(f, "%d, /* baseline */\n", baseline);
    fprintf(f, "{\n");
    for (int i = 0; i < MAX_CHARS; i++) {
        if ((unsigned)i >= 32 && i != 127)
            fprintf(f, "    { // %d \"%c\"\n", i, (char)i);
        else
            fprintf(f, "    { // %d\n", i);

        if (chars[i].image == NULL) {
            fprintf(f, "        0, /* offset */\n");
            fprintf(f, "        0, /* w */\n");
            fprintf(f, "        0, /* h */\n");
            fprintf(f, "        0, /* yoff */\n");
            fprintf(f, "        0, /* xadv */\n");
        } else {
            fprintf(f, "        %d, /* offset */\n", chars[i].fontChar.offset);
            fprintf(f, "        %d, /* w */\n", chars[i].fontChar.w);
            fprintf(f, "        %d, /* h */\n", chars[i].fontChar.h);
            fprintf(f, "        %d, /* yoff */\n", chars[i].fontChar.yoff);
            fprintf(f, "        %d, /* xadv */\n", chars[i].fontChar.xadv);
        }

        fprintf(f, "    },\n");
    }
    fprintf(f, "}\n");

    fclose(f);
}
