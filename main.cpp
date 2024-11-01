#include "mainHeader.h"
#include "LogUtils.h"
#include "DriverUtils.h"

#define CreateTimer(timerHandle) CreateTimerQueueTimer(&timerHandle, NULL, (WAITORTIMERCALLBACK)StopCapture, NULL, CAPTURE_TIME, 0, WT_EXECUTEDEFAULT);
#define DeleteTimer(timerHandle) (void)DeleteTimerQueueTimer(NULL, &timerHandle, NULL);    

// Global variable to control capture state

BOOLEAN captureOn = TRUE;
BOOLEAN loadDriver = TRUE;

VOID CALLBACK StopCapture() {
    captureOn = FALSE;
    return;
}

int main(int argc, char** argv) {
    // Handle declarations
    SC_HANDLE hService, hSCManager;
    DRIVER_SETTINGS DriverSettings;
    HANDLE timerHandle, DriverHandle;
    FILE *logFile,*RegLog, *FSLog, *LoadLog, *ProcLog;
    wchar_t DriverName[] = DRIVER_NAME;
    STARTUPINFO StartUpInfo = {sizeof StartUpInfo};
    PROCESS_INFORMATION ProcessInformation;
    DWORD BytesReturned;
    INFO Info;
    CHAR um_msg[] = "Alo do modo de usuario\n";


    fopen_s(&RegLog, "reg.xml", "w");
    fopen_s(&FSLog, "fs.xml", "w");
    fopen_s(&LoadLog, "load.xml", "w");
    fopen_s(&ProcLog, "proc.xml", "w");

    logFile = NULL;

    if (loadDriver)
        LoadDriver(&hService, &hSCManager, DriverName);

    DriverHandle = GetDriverHandle(DriverName);

    DriverSettingsSetup(&DriverSettings, argc, argv);
    
    BOOL ProcStatus = CreateProcess(
        DriverSettings.TargetName,
        NULL,
        NULL,
        NULL,
        FALSE,
        CREATE_SUSPENDED,
        NULL,
        NULL,
        &StartUpInfo,
        &ProcessInformation
    );

    if (ProcStatus)
        printf("Process Created %d\n", ProcStatus);
    else 
        printf("Process Creation failed %d %ul\n", ProcStatus, GetLastError());


    DriverSettings.TargetPid = ProcessInformation.dwProcessId;

    printf("DriverSetting.TargetPid: %ul %ul\n", ProcessInformation.dwProcessId, ProcessInformation.hProcess);

    SendDriverSettings(DriverHandle, &DriverSettings);

    CreateTimer(timerHandle);

    ResumeThread(ProcessInformation.hThread);

    fprintf(RegLog, "[\n");
    fprintf(FSLog, "[\n");
    fprintf(LoadLog, "[\n");
    fprintf(ProcLog, "[\n");
    // Main loop for capturing
    while (captureOn) {
        // Send IOCTL to driver to capture information
        BytesReturned = 0;

        DeviceIoControl(DriverHandle, IOCTL_GET_INFO,
            &um_msg, sizeof(um_msg), &Info,
            sizeof Info, &BytesReturned,
            NULL);

        // Log captured information if any
        if (BytesReturned > 0)
            switch (Info.InfoType) {
            case INFO_FS:
                logFile = FSLog;
                break;
            case INFO_REG:
                logFile = RegLog;
                break;
            case INFO_PROC:
                logFile = ProcLog;
                break;
            case INFO_LOAD:
                logFile = LoadLog;
                break;
            }

            LogInfo(Info, logFile);

    }
    fprintf(RegLog, "]\n");
    fprintf(FSLog, "]\n");
    fprintf(LoadLog, "]\n");
    fprintf(ProcLog, "]\n");


    DeleteTimer(timerHandle);

    if(loadDriver)
        UnloadDriver(&hService, &hSCManager);

    CloseHandle(DriverHandle);

    return 0;
}
