#include "../mainHeader.h"
#include "../LogUtils.h"

static inline void LogMjFunc(UCHAR MjFunc, FILE* logFile) {
    fprintf(logFile, "\"mjFunc\": ");
    switch (MjFunc) {
    case IRP_MJ_WRITE:
        fprintf(logFile, "\"IRP_MJ_WRITE\"");
        break;
    case IRP_MJ_READ:
        fprintf(logFile, "\"IRP_MJ_READ\"");
        break;
    case IRP_MJ_CREATE:
        fprintf(logFile, "\"IRP_MJ_CREATE\"");
        break;
    default:
        fprintf(logFile, "\"NOT IMPLEMENTED\"");
    }
    fprintf(logFile, ",\n");
}

static inline void LogProcInfo(PROC_INFO ProcInfo, FILE* logFile) {
    fprintf(logFile, "\"pid\": \"%lu\",\n", ProcInfo.PID);
    fprintf(logFile, "\"tid\": \"%lu\",\n", ProcInfo.TID);
    fprintf(logFile, "\"sid\": \"%lu\",\n", ProcInfo.SID);
    printf("\"pid\": \"%p\",\n", &ProcInfo);
    printf("\"pid\": \"%p\",\n", &ProcInfo.PID);
    printf("\"tid\": \"%p\",\n", &ProcInfo.TID);
    printf("\"sid\": \"%p\",\n", &ProcInfo.SID);

    LogTokenInfo(ProcInfo.TokenInfo, logFile);

    fprintf(logFile, "\"image name\": \"%ws\",\n", ProcInfo.ImageName);
}

void LogFileInfo(PFILE_INFO FileInfo, FILE* logFile) {
    fprintf(logFile, "\"path\": \"%ws\",\n", FileInfo->Path);
    fprintf(logFile, "\"fileName\": \"%ws\"\n", FileInfo->FinalName);
}

void LogFsInfo(FS_INFO FsInfo, FILE* logFile) {
    LogMjFunc(FsInfo.MjFunc, logFile);
    LogProcInfo(FsInfo.ProcInfo, logFile);
    LogFileInfo(&FsInfo.FileInfo, logFile);
}
