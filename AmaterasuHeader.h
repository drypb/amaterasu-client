#ifndef WDM_H
#define WDM_H

#include <windows.h>
#include "wdm.h"

// Maximum count for privileges
#define MAX_PRIV_COUNT 35

// Maximum data size
#define MAX_DATA 2048

// Number of callback types
#define CALLBACK_NUMBER 4

// IOCTL control codes
#define IOCTL_GET_INFO CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)
#define IOCTL_AMATERASU_SETUP CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_READ_DATA | FILE_WRITE_DATA)

// Enum for information types
enum InfoType {
    INFO_FS,    // File system info
    INFO_PROC,  // Process info
    INFO_REG,   // Registry info
    INFO_LOAD   // Load image info
};

typedef enum InfoType INFO_TYPE, * PINFO_TYPE;

// Enum for filter modes
enum _filtermode {
    SYSTEM_WIDE,    // System-wide filtering
    PROCESS_BASED   // Process-based filtering
};

typedef _filtermode FILTER_MODE, * PFILTER_MODE;

// Structure for driver settings
struct _DriverSettings {
    BOOLEAN EnabledCallbacks[CALLBACK_NUMBER];                  // Are callbacks enabled
    ULONG MaxRecords;     // Max records for each callback
    WCHAR TargetName[MAX_PATH+1];   // Target name
    ULONG TargetNameSize;
    ULONG TargetPid;

};

typedef struct _DriverSettings DRIVER_SETTINGS, * PDRIVER_SETTINGS;

// Structure for privileges
struct privileges {
    DWORD PrivilegeCount;                      // Count of privileges
    LUID_AND_ATTRIBUTES Privileges[MAX_PRIV_COUNT];  // Array of privileges
};

typedef struct privileges PRIVILEGES, * PPRIVILEGES;

// Structure for token information
struct TokenInfo {
    TOKEN_TYPE Type;                           // Token type
    PRIVILEGES Privileges;                     // Associated privileges
    TOKEN_ELEVATION TokenElevation;            // Elevation status
    SECURITY_IMPERSONATION_LEVEL ImpersonationLevel;  // Impersonation level
};

typedef struct TokenInfo TOKEN_INFO, * PTOKEN_INFO;

// Structure for process information
struct ProcInfo {
    WCHAR ImageName[MAX_PATH];                 // Image name of the process
    ULONG PID;                                 // Process ID
    ULONG SID;                                 // Session ID
    ULONG TID;                                 // Thread ID
    TOKEN_INFO TokenInfo;                      // Token information
};

typedef struct ProcInfo PROC_INFO, * PPROC_INFO;

// Structure for file information
struct FileInfo {
    WCHAR FinalName[MAX_PATH];                 // Final name of the file
    WCHAR Path[MAX_PATH];                      // Path of the file

};

typedef struct FileInfo FILE_INFO, * PFILE_INFO;

// Structure for file system information
struct FsInfo {
    UCHAR MjFunc;                              // Major function code
    FILE_INFO FileInfo;                        // File information
    PROC_INFO ProcInfo;                        // Process information
};

typedef struct FsInfo FS_INFO, * PFS_INFO;

// Structure for load image information
struct _LoadImageInfo {
    IMAGE_INFO ImageInfo;                      // Image information structure
    HANDLE PID;                                // Process ID
    ULONG FullImageNameSize;                   // Size of the full image name
    ULONG FileNameSize;                        // Size of the file name
    WCHAR FullImageName[MAX_PATH];             // Full image name
    WCHAR FileName[MAX_PATH];                  // File name
};

typedef struct _LoadImageInfo LOAD_IMAGE_INFO, * PLOAD_IMAGE_INFO;

// Structure for identifiers
struct IDENTIFIER {
    HANDLE PPID;                               // Parent process ID
    union {
        HANDLE PID;                            // Process ID
        HANDLE TID;                            // Thread ID
        HANDLE ID;                             // Generic ID
    } Id;
    BOOLEAN isThread;                          // Is this a thread identifier
    BOOLEAN Active;                            // Is the identifier active
};

typedef struct IDENTIFIER IDENTIFIER, * PIDENTIFIER;

// Structure for process data
struct ProcData {
    IDENTIFIER Ids;                            // Identifiers
    TOKEN_INFO TokenInfo;                      // Token information
    WCHAR ParentName[MAX_PATH];                // Parent process name
    WCHAR ChildName[MAX_PATH];                 // Child process name
};

typedef struct ProcData PROC_DATA, * PPROC_DATA;

// Structure for registry information
struct RegInfo {
    REG_NOTIFY_CLASS RegNotifyClass;           // Registry notification class
    WCHAR CompleteName[MAX_PATH];              // Complete name of the registry key
    ULONG CompleteNameSize;                    // Size of the complete name
    WCHAR Data[MAX_DATA];                      // Data associated with the registry key
    ULONG DataSize;                            // Size of the data
    ULONG DataType;                            // Type of the data
};

typedef struct RegInfo REG_INFO, * PREG_INFO;

// Union for holding different types of information
struct info {
    TIME_FIELDS TimeFields;                    // Time fields structure
    INFO_TYPE InfoType;                        // Type of information
    union {
        FS_INFO FsInfo;                        // File system information
        REG_INFO RegInfo;                      // Registry information
        PROC_DATA ProcData;                    // Process data
        LOAD_IMAGE_INFO LoadImageInfo;         // Load image information
        PVOID Data;                            // Generic data pointer
    } Info;
};

typedef struct info INFO, * PINFO;

#endif // WDM_H
