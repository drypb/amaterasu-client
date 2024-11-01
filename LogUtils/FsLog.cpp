#include "../mainHeader.h"
#include "../LogUtils.h"

static inline void LogMjFunc(UCHAR MjFunc, FILE* logFile) {
    tag(logFile, "mj_func");
    switch (MjFunc) {
    case IRP_MJ_WRITE:
        fprintf(logFile, "IRP_MJ_WRITE");
        break;
    case IRP_MJ_READ:
        fprintf(logFile, "IRP_MJ_READ");
        break;
    case IRP_MJ_CREATE:
        fprintf(logFile, "IRP_MJ_CREATE");
        break;
    default:
        fprintf(logFile, "NOT_IMPLEMENTED");
    }
    endtag(logFile, "mj_func");
}

static inline void LogProcInfo(PROC_INFO ProcInfo, FILE* logFile) {
    log(logFile, "pid", ProcInfo.PID);
    log(logFile, "tid", ProcInfo.TID);
    log(logFile, "sid", ProcInfo.SID);

    LogTokenInfo(ProcInfo.TokenInfo, logFile);

    log(logFile, "image_name", ProcInfo.ImageName);
}

void LogFileInfo(PFILE_INFO FileInfo, FILE* logFile) {
    log(logFile, "path", FileInfo->Path);
    log(logFile, "file_name", FileInfo->FinalName);
}

void LogFsInfo(FS_INFO FsInfo, FILE* logFile) {
    LogMjFunc(FsInfo.MjFunc, logFile);
    LogProcInfo(FsInfo.ProcInfo, logFile);
    LogFileInfo(&FsInfo.FileInfo, logFile);
}
