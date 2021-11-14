#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define STRUCT(X) \
    struct X; \
    typedef struct X X; \
    struct X

STRUCT(Function)
{
    Function* next;
    char name[256];
    unsigned addr;
};

STRUCT(Section)
{
    Section* next;
    char name[256];
    Function* firstFunc;
    Function* lastFunc;
    unsigned startAddr;
    unsigned head;
    unsigned tail;
    int funcCount;
    bool exists;
};

Section* firstSection;
Section* lastSection;
int sectionCount;

Section* FindSection(const char* name)
{
    for (Section* p = firstSection; p; p = p->next) {
        if (!strcmp(p->name, name))
            return p;
    }

    Section* section = (Section*)malloc(sizeof(Section));
    if (!section) {
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }

    strcpy(section->name, name);
    section->next = NULL;
    section->startAddr = 0;
    section->head = 0;
    section->tail = 0;
    section->firstFunc = NULL;
    section->lastFunc = NULL;
    section->funcCount = 0;
    section->exists = false;

    if (!firstSection)
        firstSection = section;
    else
        lastSection->next = section;
    lastSection = section;
    ++sectionCount;

    return section;
}

Function* AddFunc(Section* sect, const char* name, unsigned addr)
{
    Function* func = (Function*)malloc(sizeof(Function));
    if (!func) {
        fprintf(stderr, "out of memory!\n");
        exit(1);
    }

    strcpy(func->name, name);
    func->next = NULL;
    func->addr = addr;

    if (!sect->firstFunc) {
        sect->firstFunc = func;
        sect->startAddr = addr;
    } else {
        sect->lastFunc->next = func;
        if (addr < sect->startAddr)
            sect->startAddr = addr;
    }
    sect->lastFunc = func;
    sect->funcCount++;

    return func;
}

int CompareSections(const void* p1, const void* p2)
{
    const Section* s1 = *(const Section**)p1;
    const Section* s2 = *(const Section**)p2;

    if (s1->head < s2->head)
        return -1;
    else if (s1->head > s2->head)
        return 1;
    return 0;
}

int CompareFunctions(const void* p1, const void* p2)
{
    const Function* f1 = *(const Function**)p1;
    const Function* f2 = *(const Function**)p2;

    if (f1->addr < f2->addr)
        return -1;
    else if (f1->addr > f2->addr)
        return 1;
    return 0;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Invalid command line.");
        return 1;
    }

    FILE* f = fopen(argv[1], "r");
    if (!f) {
        fprintf(stderr, "Can't open %s: %s", argv[1], strerror(errno));
        return 1;
    }

    char buf[4096];
    int line = 0;
    while (fgets(buf, sizeof(buf), f)) {
        char* p = strchr(buf, '=');
        *p = 0;

        char* end = p;
        while (end > buf && *(end - 1) == ' ')
            *--end = 0;

        char* name = buf;
        ++p;
        ++p;
        if (*p != '$') {
            fprintf(stderr, "not '$'.\n");
            fclose(f);
            return 1;
        }

        ++p;
        const char* hex = p;
        while (*p != ' ')
            ++p;
        *p = 0;

        ++p;
        if (*p != ';') {
            fprintf(stderr, "not ';'.\n");
            fclose(f);
            return 1;
        }

        ++p;
        if (*p != ' ') {
            fprintf(stderr, "not ' '.\n");
            fclose(f);
            return 1;
        }

        ++p;
        const char* access = p;
        while (*p != ',')
            ++p;
        *p = 0;

        ++p;
        if (*p != ' ') {
            fprintf(stderr, "not ' '.\n");
            fclose(f);
            return 1;
        }

        ++p;
        const char* vis = p;
        while (*p != ',')
            ++p;
        *p = 0;

        while (*p != ',')
            ++p;

        ++p;
        if (*p != ' ') {
            fprintf(stderr, "1 not ' '.\n");
            fclose(f);
            return 1;
        }

        ++p;
        const char* file = p;
        while (*p != ',')
            ++p;
        *p = 0;

        ++p;
        if (*p != ' ') {
            fprintf(stderr, "2 not ' '.\n");
            fclose(f);
            return 1;
        }

        ++p;
        const char* section = p;
        while (*p != ',')
            ++p;
        *p = 0;

        char* location = (char*)"";

        ++p;
        if (*p != '\n' && *p != 0) {
            if (*p != ' ') {
                fprintf(stderr, "3 not ' '.\n");
                fclose(f);
                return 1;
            }

            ++p;
            location = p;

            size_t len = strlen(location);
            if (len > 0 && location[len - 1] == '\n')
                location[len - 1] = 0;
        }

        Section* s = FindSection(section);
        s->exists = true;

        unsigned addr = strtol(hex, NULL, 16);
        /*
        if (addr < 0x4000)
            continue;
        if (addr > 0xffff)
            continue;
        */

        size_t len = strlen(name);
        /*
        if (len > 4 && !memcmp(name, "__IO", 4))
            continue;
        if (len > 8 && !memcmp(name, "__SYSVAR", 8))
            continue;
        if (!strcmp(name, "__SYS_IY"))
            continue;
        if (len > 6 && !memcmp(name, "IOCTL_", 6))
            continue;
        if (len > 5 && !memcmp(name, "SP1V_", 5))
            continue;
        if (len > 9 && !memcmp(name, "__NIRVANA", 9))
            continue;
        if (len > 9 && !memcmp(name, "__BIFROST", 9))
            continue;
        if (len > 10 && !memcmp(name, "__CLIB_OPT", 10))
            continue;
        if (len > 5 && !memcmp(name, "__CLK", 5))
            continue;
        if (len > 8 && !memcmp(name, "_NIRVANA", 8))
            continue;
        if (len > 8 && !memcmp(name, "_BIFROST", 8))
            continue;
        */

        if (len > 5 && name[len - 5] == '_') {
            if (!memcmp(&name[len - 4], "head", 4)) {
                name[len - 5] = 0;
                FindSection(&name[2])->head = addr;
                continue;
            }

            if (!memcmp(&name[len - 4], "tail", 4)) {
                name[len - 5] = 0;
                FindSection(&name[2])->tail = addr;
                continue;
            }
        }

        if (!strcmp(access, "const"))
            continue;

        Function* f = AddFunc(s, name, addr);
    }

    fclose(f);

    Section** sections = (Section**)malloc(sectionCount * sizeof(Section*));
    if (!sections) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    int i = 0;
    for (Section* s = firstSection; s; s = s->next)
        sections[i++] = s;

    qsort(sections, sectionCount, sizeof(Section*), CompareSections);

    Function** funcs = NULL;
    int funcsSize = 0;

    for (i = 0; i < sectionCount; i++) {
        Section* s = sections[i];
        if (!s->exists)
            continue;

        if (s->funcCount == 0)
            continue;

        printf("[%04X..%04X] %s\n", s->head, s->tail, s->name);

        if (s->funcCount > funcsSize) {
            funcs = (Function**)realloc(funcs, sizeof(Function**) * s->funcCount);
            if (!funcs) {
                fprintf(stderr, "out of memory\n");
                free(sections);
                return 1;
            }
            funcsSize = s->funcCount;
        }

        int j = 0;
        for (Function* f = s->firstFunc; f; f = f->next)
            funcs[j++] = f;

        qsort(funcs, s->funcCount, sizeof(Function*), CompareFunctions);

        for (j = 0; j < s->funcCount; j++) {
            Function* f = funcs[j];
            printf("  - (%04X) %s\n", f->addr, f->name);
        }
    }

    free(funcs);
    free(sections);

    return 0;
}
