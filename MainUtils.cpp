#include "mainHeader.h"
#include "LogUtils.h"
#include "DriverUtils.h"

void InfoQuery(FILE* logFile, HANDLE DriverHandle) {
    DWORD BytesReturned;
    INFO Info;
    CHAR um_msg[] = "Alo do modo de usuario\n";

    fprintf(logFile, "[\n");
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
            LogInfo(Info, logFile);
        else
            printf("BytesReturned %ul\n", BytesReturned);

    }
    fprintf(logFile, "]\n");
}

HANDLE StartDriver(SC_HANDLE* hService, SC_HANDLE* hSCManager, wchar_t DriverName[]) {

    // Load the driver
    if (loadDriver)
        LoadDriver(hService, hSCManager, DriverName);

    printf("D: %ws", DriverName);
    // Get a handle to the driver
    return GetDriverHandle(DriverName);
}