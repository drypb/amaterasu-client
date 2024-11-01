#include "mainHeader.h"
#include "LogUtils.h"

/**
 * LogTime - Log time information
 * @TimeFields: TIME_FIELDS struct containing time details
 * @logFile: FILE pointer to the log file
 *
 * Logs the date and time of the event.
 */
static inline void LogTime(TIME_FIELDS TimeFields, FILE* logFile)
{
    tag(logFile, "date");
    fprintf(logFile, "%d/%d/%d", TimeFields.Day, TimeFields.Month, TimeFields.Year);
    endtag(logFile, "date");

    tag(logFile, "time");
    fprintf(logFile, "%d:%d:%d:%d", TimeFields.Hour, TimeFields.Minute, TimeFields.Second,TimeFields.Milliseconds);
    endtag(logFile, "time");
}

/**
 * LogInfoType - Log info type
 * @InfoType: INFO_TYPE enum containing the type of information
 * @logFile: FILE pointer to the log file
 *
 * Logs the type of information (filesystem, process, load image, registry).
 */
static inline void LogInfoType(INFO_TYPE InfoType, FILE* logFile)
{
    tag(logFile, "info_type");
    switch (InfoType) {
    case INFO_FS:
        fprintf(logFile, "INFO_FS");
        break;
    case INFO_PROC:
        fprintf(logFile, "INFO_PROC");
        break;
    case INFO_LOAD:
        fprintf(logFile, "INFO_LOAD");
        break;
    case INFO_REG:
        fprintf(logFile, "INFO_REG");
        break;
    default:
        fprintf(logFile, "INVALID INFO TYPE");
        break;
    }
    endtag(logFile, "info_type");
}

/**
 * LogBaseInfo - Log basic information
 * @Info: INFO struct containing basic information
 * @logFile: FILE pointer to the log file
 *
 * Logs the time and type of information.
 */
static inline void LogBaseInfo(INFO Info, FILE* logFile)
{
    LogTime(Info.TimeFields, logFile);
    LogInfoType(Info.InfoType, logFile);
}




/*
 * LogInfo - Log information based on IOCTL code
 * @Info: INFO struct containing information to be logged
 * @logFile: FILE pointer to the log file
 * @IOCTL_CODE: DWORD representing the IOCTL code
 *
 * Logs information based on the IOCTL code. Currently, only supports logging file information.
 */
void LogInfo(INFO Info, FILE* logFile) {
    printf("entrou no log info\n");
    tag(logFile, "log");
    LogBaseInfo(Info, logFile);

    switch (Info.InfoType) {
    case INFO_FS:
        LogFsInfo(Info.Info.FsInfo, logFile);
        break;
    case INFO_REG:
        LogRegInfo(Info.Info.RegInfo, logFile);
        break;
    case INFO_PROC:
        LogProcData(Info.Info.ProcData, logFile);
        break;
    case INFO_LOAD:
        LogLoadImage(Info.Info.LoadImageInfo, logFile);
        break;
    default:

        printf("Invalid Type code given\n");
        break;
    }
    endtag(logFile, "log");

    fflush(logFile); // Flush the buffer after each write
}
