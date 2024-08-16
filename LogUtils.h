#ifndef LOG_UTILS_H
#define LOG_UTILS_H

#include "mainHeader.h"

void LogTokenInfo(TOKEN_INFO TokenInfo, FILE* logFile);

void LogRegInfo(REG_INFO RegInfo, FILE* logFile);

void LogProcData(PROC_DATA  ProcData, FILE* logFile);

void LogLoadImage(LOAD_IMAGE_INFO LoadImageInfo, FILE* logFile);

void LogFsInfo(FS_INFO FsInfo, FILE* logFile);

void LogInfo(INFO Info, FILE* logFile);


#endif