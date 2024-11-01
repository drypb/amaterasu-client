#include "../mainHeader.h"
#include "../LogUtils.h"

static void log(FILE* dest ,char* tag, char* content){
    fprintf(dest, "<%s>%s<\\%s>",tag, content, tag);
}

static void log(FILE* dest ,char* tag, PWSTR content){
    fprintf(dest, "<%s>%ws<\\%s>",tag, content, tag);
}

static void log(FILE* dest ,char* tag, int content){
    fprintf(dest, "<%s>%d<\\%s>",tag, content, tag);
}

static void log(FILE* dest ,char* tag, ULONG content){
    fprintf(dest, "<%s>%lu<\\%s>",tag, content, tag);
}

static void log(FILE* dest ,char* tag, ULONGLONG content){
    fprintf(dest, "<%s>%llu<\\%s>",tag, content, tag);
}


static FILE* tag(FILE* dest, char* tag){
    fprintf(dest, "<%s>", tag);
}

static FILE* endtag(FILE* dest, char* tag){
    fprintf(dest, "<\%s>", tag);
}
