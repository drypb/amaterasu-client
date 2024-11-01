#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include "mainHeader.h"

void LogTokenInfo(TOKEN_INFO TokenInfo, FILE* logFile);

void LogRegInfo(REG_INFO RegInfo, FILE* logFile);

void LogProcData(PROC_DATA  ProcData, FILE* logFile);

void LogLoadImage(LOAD_IMAGE_INFO LoadImageInfo, FILE* logFile);

void LogFsInfo(FS_INFO FsInfo, FILE* logFile);

void LogInfo(INFO Info, FILE* logFile);

void log(FILE* dest, const char* tag, const char* content);
void log(FILE* dest, const char* tag, PWSTR content);
void log(FILE* dest, WCHAR* tag, const char* content);
void log(FILE* dest, const char* tag, int content);
void log(FILE* dest, const char* tag, ULONG content);
void log(FILE* dest, const char* tag, ULONGLONG content);


void tag(FILE* dest, const char* tag);

void endtag(FILE* dest, const char* tag);



#endif
