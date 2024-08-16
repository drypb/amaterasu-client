#pragma once
#include <stdio.h>
#include <iostream>
#include "AmaterasuHeader.h"

#define CAPTURE_TIME 300000
#define DRIVER_NAME L"MiniFilter"

//#define fprintf(a,b,...) printf(b, __VA_ARGS__)

extern BOOLEAN loadDriver;
extern BOOLEAN captureOn;

void InfoQuery(FILE* logFile, HANDLE DriverHandle);

HANDLE StartDriver(SC_HANDLE* hService, SC_HANDLE* hSCManager, wchar_t DriverName[]);


