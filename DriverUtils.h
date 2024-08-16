#include "mainHeader.h"
#define EnableFsCallback(DriverSettings) DriverSettings->EnabledCallbacks[0] = 1
#define EnableProcCallback(DriverSettings) DriverSettings->EnabledCallbacks[1] = 1
#define EnableLoadCallback(DriverSettings) DriverSettings->EnabledCallbacks[2] = 1
#define EnableRegCallback(DriverSettings) DriverSettings->EnabledCallbacks[3] = 1
#define EnableAllCallbascks(DriverSettings) memset(DriverSettings->EnabledCallbacks, 1, CALLBACK_NUMBER * sizeof(BOOLEAN))

#define SetSystemWideCapture(DriverSettings) DriverSettings->FilterMode = SYSTEM_WIDE
#define SetProcessBasedCapture(DriverSettings) DriverSettings->FilterMode = PROCESS_BASED

#define SetMaxRecords(DriverSettings, MaxRec) DriverSettings->MaxRecords = atoi(MaxRec);


#define SetProcessTargetName(DriverSettings, Src) mbstowcs(DriverSettings->TargetName, Src, strlen(Src));


/*
 * LoadDriver - Loads Driver
 *
 * @hService: pointer to a SC_HANDLE for opening a service
 *
 * @hSCManager: pointer to a SC_HANDLE to estabilish a connection to the SC manager
 *
 * Return:
 * 	- TRUE the driver was loaded
 * 	- FALSE failed to load the driver
 */

BOOLEAN LoadDriver(_Out_ SC_HANDLE* hService, _Out_ SC_HANDLE* hSCManager, _In_ wchar_t* DriverName);

/*
 * UnloadDriver - Unloads Driver
 *
 * @hService: pointer to a SC_HANDLE for stoping the driver and be closed
 *
 * @hSCManager: pointer to a SC_HANDLE to be closed
 *
 */
void UnloadDriver(_In_ SC_HANDLE* hService, _In_ SC_HANDLE* hSCManager);

HANDLE GetDriverHandle(wchar_t* DriverName);

NTSTATUS DriverSettingsSetup(PDRIVER_SETTINGS DriverSettings, int argc, char** argv);

BOOLEAN SendDriverSettings(HANDLE DriverHandle, PDRIVER_SETTINGS DriverSettings);

void PrintDriverSettings(PDRIVER_SETTINGS DriverSettings);

