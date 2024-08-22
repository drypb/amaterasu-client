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
    fprintf(logFile, "\"ppid\": \"%lu\",\n", Ids.PPID);

    if (Ids.isThread) {
        fprintf(logFile, "\"tid\": \"%lu\",\n", Ids.Id.ID);
    }
    else {
        fprintf(logFile, "\"pid\": \"%lu\",\n", Ids.Id.ID);
    }

    fprintf(logFile, "\"operation\": \"%s\",\n", Ids.Active ? "create" : "kill");
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

    fprintf(logFile, "\"parent name\": \"%ws\",\n", ProcData.ParentName);
    fprintf(logFile, "\"child name\": \"%ws\"\n", ProcData.ChildName);
}
