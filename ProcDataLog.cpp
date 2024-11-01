#include "../mainHeader.h"
#include "../LogUtils.h"

/**
 * LogIds - Log identifier information
 * @Ids: IDENTIFIER struct containing identifier details
 * @logFile: FILE pointer to the log file
 *
 * Logs process and thread IDs, and the operation (create or kill).
 */
static inline void LogIds(IDENTIFIER Ids, FILE* logFile)
{
    log(logFile, "ppid", (ULONG)Ids.PPID);

    if (Ids.isThread) {
        log(logFile, "tid", (ULONG)Ids.Id.ID);
    }
    else {
        log(logFile, "pid", (ULONG)Ids.Id.ID);
    }

    log(logFile, "operation", Ids.Active ? "create" : "kill");
}

/**
 * LogProcData - Log process data
 * @ProcData: PROC_DATA struct containing process data details
 * @logFile: FILE pointer to the log file
 *
 * Logs process identifiers and token information.
 */
void LogProcData(PROC_DATA ProcData, FILE* logFile)
{
    LogIds(ProcData.Ids, logFile);
    LogTokenInfo(ProcData.TokenInfo, logFile);

    log(logFile, "parent_name", ProcData.ParentName);
    log(logFile, "child_name", ProcData.ChildName);
}
