#ifndef PROCESS_H
#define PROCESS_H

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <stdlib.h>
#include <winbase.h>

typedef struct PROCESS{
    char name[512];
    int processID;
    int threadCount;
} PROCESS;

void ListProcess(int argc, char** argv);
void SearchProcess(int argc, char** argv);
void KillProcess(int argc, char** argv);
void StopProcess(int argc, char** argv);
void ResumeProcess(int argc, char** argv);
void CreateProcessBackground(int argc, char** argv, char* command);
void CreateProcessForeground(int argc, char** argv, char* command);

#endif //PROCESS_H
