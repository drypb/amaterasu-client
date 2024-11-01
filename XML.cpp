#include "../mainHeader.h"
#include "../LogUtils.h"

void log(FILE* dest , const char* tag, const char* content){
    fprintf(dest, "<%s>%s<\\%s>",tag, content, tag);
}

void log(FILE* dest , const char* tag, PWSTR content){
    fprintf(dest, "<%s>%ws<\\%s>",tag, content, tag);
}

void log(FILE* dest, WCHAR* tag, const char* content) {
    fprintf(dest, "<%ws>%s<\\%ws>",tag, content, tag);
}

void log(FILE* dest , const char* tag, int content){
    fprintf(dest, "<%s>%d<\\%s>",tag, content, tag);
}

void log(FILE* dest , const char* tag, ULONG content){
    fprintf(dest, "<%s>%lu<\\%s>",tag, content, tag);
}

void log(FILE* dest , const char* tag, ULONGLONG content){
    fprintf(dest, "<%s>%llu<\\%s>",tag, content, tag);
}


void tag(FILE* dest, const char* tag){
    fprintf(dest, "<%s>", tag);
}

void endtag(FILE* dest, const char* tag){
    fprintf(dest, "<\\%s>", tag);
}
