/*
 * Copyright (c) 2021 DrunkFly Team
 * Licensed under 3-clause BSD license
 */
#include "importer.h"
#include "stb_image.h"

#define MAX_FONTS 256
#define MAX_CHARS 256

STRUCT(Char)
{
    FontChar fontChar;
    int offset;
    byte* image;
};

STRUCT(Image)
{
    stbi_uc* image;
    int width;
    int height;
};

STRUCT(FontListEntry)
{
    char name[256];
    byte bank;
    int firstChar;
    int lineH;
    int baseline;
    int size;
};

static FontListEntry fontList[MAX_FONTS];
static int fontCount;

static Image* images;
static int imageCount;

static Char chars[MAX_CHARS];

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

    FontListEntry* fontEntry = &fontList[fontCount];
    fontCount++;

    fscanf(f, "info face=%s size=%d bold=%d italic=%d charset=%s unicode=%d stretchH=%d smooth=%d aa=%d padding=%d,%d,%d,%d spacing=%d,%d outline=%d\n",
        face, &size, &bold, &italic, charset, &unicode, &stretchH,
        &smooth, &aa, &paddingX, &paddingY, &paddingW, &paddingH,
        &spacingX, &spacingY, &outline);

    fscanf(f, "common lineHeight=%d base=%d scaleW=%d scaleH=%d pages=%d packed=%d alphaChnl=%d redChnl=%d greenChnl=%d blueChnl=%d\n",
        &fontEntry->lineH, &fontEntry->baseline, &scaleW, &scaleH, &pages, &packed,
        &alphaChnl, &redChnl, &greenChnl, &blueChnl);

    images = (Image*)calloc(pages, sizeof(Image));
    if (!images) {
        fclose(f);
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }

    char* slash = strrchr(file, '/');
    strcpy(fontEntry->name, (slash ? slash + 1 : file));
    char* ext = strrchr(fontEntry->name, '.');
    if (ext)
        *ext = 0;
    for (char* p = fontEntry->name; *p; p++) {
        if (*p == '.')
            *p = '_';
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
            fprintf(stderr, "error: can't load \"%s\": %s\n", path, stbi_failure_reason());
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
    int count = 0;
    fontEntry->firstChar = -1;

    for (int i = 0; i < numChars; i++) {
        int id, imgX, imgY, width, height, xoff, yoff, xadv, page, chnl;
        fscanf(f, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d page=%d chnl=%d\n",
            &id, &imgX, &imgY, &width, &height, &xoff, &yoff, &xadv, &page, &chnl);

        if (id > 255)
            continue;

        // FIXME: hack!
        if (xoff < 0) {
            xadv += -xoff;
            width += -xoff;
            xoff = 0;
        }

        if (fontEntry->firstChar < 0 || id < fontEntry->firstChar)
            fontEntry->firstChar = id;

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

        chars[id].fontChar.w = (byte)w;
        chars[id].fontChar.h = (byte)height;
        chars[id].fontChar.yoff = (byte)yoff;
        chars[id].fontChar.xadv = (byte)xadv;
        chars[id].offset = (word)offset;

        offset += w * height;
        ++count;
    }

    fontEntry->size = offset + sizeof(Font)
                    + sizeof(FontChar) * count;
                    + sizeof(Font);

    fclose(f);

    char bankFile[256];
    fontEntry->bank = requestBank(fontEntry->name, fontEntry->size, bankFile, sizeof(bankFile));

    createDirectories(bankFile);
    f = fopen(bankFile, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    fprintf(f, "#include \"engine.h\"\n");
    fprintf(f, "\n");
    fprintf(f, "static const unsigned char font_%s_pixels[] = {\n", fontEntry->name);

    for (int i = 0; i < MAX_CHARS; i++) {
        if (chars[i].image != NULL) {
            int off = 0;
            if ((unsigned)i >= 32 && i != 127)
                fprintf(f, "    // %d \"%c\"\n", i, (char)i);
            else
                fprintf(f, "    // %d\n", i);

            for (int y = 0; y < chars[i].fontChar.yoff; y++) {
                fprintf(f, "    ");

                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "     ");

                fprintf(f, " // ");
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "........");

                fprintf(f, "\n");
            }

            for (int y = 0; y < chars[i].fontChar.h; y++) {
                fprintf(f, "    ");

                for (int x = 0; x < chars[i].fontChar.w; x++) {
                    fprintf(f, "0x%02X,", chars[i].image[off + x]);
                    ++size;
                }

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

            for (int y = chars[i].fontChar.yoff + chars[i].fontChar.h; y < fontEntry->lineH; y++) {
                fprintf(f, "    ");

                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "     ");

                fprintf(f, " // ");
                for (int x = 0; x < chars[i].fontChar.w; x++)
                    fprintf(f, "........");

                fprintf(f, "\n");
            }
        }
    }

    fprintf(f, "};\n");
    fprintf(f, "\n");
    fprintf(f, "const FontChar font_%s_chars[] = {\n", fontEntry->name);

    for (int i = 0; i < MAX_CHARS; i++) {
        if (i < fontEntry->firstChar)
            continue;

        if ((unsigned)i >= 32 && i != 127)
            fprintf(f, "    { // %d \"%c\"\n", i, (char)i);
        else
            fprintf(f, "    { // %d\n", i);

        if (chars[i].image == NULL) {
            fprintf(f, "        NULL, /* pixels */\n");
            fprintf(f, "        0, /* w */\n");
            fprintf(f, "        0, /* h */\n");
            fprintf(f, "        0, /* yoff */\n");
            fprintf(f, "        0, /* xadv */\n");
        } else {
            fprintf(f, "        &font_%s_pixels[%d], /* pixels */\n", fontEntry->name, chars[i].offset);
            fprintf(f, "        %d, /* w */\n", chars[i].fontChar.w);
            fprintf(f, "        %d, /* h */\n", chars[i].fontChar.h);
            fprintf(f, "        %d, /* yoff */\n", chars[i].fontChar.yoff);
            fprintf(f, "        %d, /* xadv */\n", chars[i].fontChar.xadv);
        }

        fprintf(f, "    },\n");
    }

    fprintf(f, "};\n");
    fclose(f);
}

void outputFontList(const char* file)
{
    createDirectories(file);
    FILE* f = fopen(file, "w");
    if (!f) {
        fprintf(stderr, "error: can't write file \"%s\": %s\n", file, strerror(errno));
        exit(1);
    }

    for (int i = 0; i < fontCount; i++) {
        fprintf(f, "\n");
        fprintf(f, "extern const FontChar font_%s_chars[];\n", fontList[i].name);
        fprintf(f, "\n");
        fprintf(f, "const Font font_%s = {\n", fontList[i].name);
        fprintf(f, "    %d, /* lineH */\n", fontList[i].lineH);
        fprintf(f, "    %d, /* baseline */\n", fontList[i].baseline);
        fprintf(f, "    %d, /* firstChar */\n", fontList[i].firstChar);
        fprintf(f, "    %d, /* bank */\n", fontList[i].bank);
        fprintf(f, "    font_%s_chars, /* chars */\n", fontList[i].name);
        fprintf(f, "};\n");
    }

    fclose(f);
}
