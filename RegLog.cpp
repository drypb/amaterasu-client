#include "../mainHeader.h"
#include "../LogUtils.h"
/**
 * LogRegClass - Log registry notification class
 * @RegNotifyClass: REG_NOTIFY_CLASS enum containing registry notification details
 * @logFile: FILE pointer to the log file
 *
 * Logs the type of registry operation.
 */
static inline void LogRegClass(REG_NOTIFY_CLASS RegNotifyClass, FILE* logFile)
{
    tag(logFile, "registry_operation");
    switch (RegNotifyClass) {
    case RegNtSetValueKey:
        fprintf(logFile, "RegNtSetValueKey");
        break;
    case RegNtDeleteValueKey:
        fprintf(logFile, "RegNtDeleteValueKey");
        break;
    default:
        fprintf(logFile, "not implemented");
        break;
    }
    endtag(logFile, "registry_operation");
}

/**
 * LogRegName - Log registry name
 * @Name: PWSTR containing the registry name
 * @logFile: FILE pointer to the log file
 *
 * Logs the name of the registry key or value.
 */
static inline void LogRegName(PWSTR Name, FILE* logFile)
{
    log(logFile, "name", Name);
}

/**
 * LogRegDataType - Log registry data type
 * @Type: ULONG containing the registry data type
 * @logFile: FILE pointer to the log file
 *
 * Logs the type of data stored in the registry key or value.
 */
static inline void LogRegDataType(ULONG Type, FILE* logFile)
{
    tag(logFile, "data_type");
    switch (Type) {
    case REG_SZ:
        fprintf(logFile, "REG_SZ");
        break;
    case REG_EXPAND_SZ:
        fprintf(logFile, "REG_EXPAND_SZ");
        break;
    case REG_MULTI_SZ:
        fprintf(logFile, "REG_MULTI_SZ");
        break;
    case REG_BINARY:
        fprintf(logFile, "REG_BINARY");
        break;
    case REG_DWORD:
        fprintf(logFile, "REG_DWORD");
        break;
    case REG_QWORD:
        fprintf(logFile, "REG_QWORD");
        break;
    }
    endtag(logFile, "data_type");
}

/**
 * LogRegData - Log registry data
 * @Data: PWSTR containing the registry data
 * @logFile: FILE pointer to the log file
 *
 * Logs the actual data stored in the registry key or value.
 */
static inline void LogRegData(PWSTR Data, FILE* logFile)
{
    log(logFile, "data", Data);
}

/**
 * LogRegInfo - Log registry information
 * @RegInfo: REG_INFO struct containing registry details
 * @logFile: FILE pointer to the log file
 *
 * Logs information about registry operations, including class, name, data type, and data.
 */
void LogRegInfo(REG_INFO RegInfo, FILE* logFile)
{
    LogRegClass(RegInfo.RegNotifyClass, logFile);
    LogRegName(RegInfo.CompleteName, logFile);
    LogRegDataType(RegInfo.DataType, logFile);
    LogRegData(RegInfo.Data, logFile);
    if (RegInfo.RegNotifyClass == RegNtSetValueKey) {
        LogRegData(RegInfo.Data, logFile);
    }
}
