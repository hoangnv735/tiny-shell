#include "process.h"
#include "macro.h"

typedef LONG (NTAPI * NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG (NTAPI * NtResumeProcess)(IN HANDLE ProcessHandle);

PROCESS_INFORMATION* piPointer;

void printError() {
  DWORD eNum;
  char sysMsg[256];
  char* p;

  eNum = GetLastError( );
  FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL, eNum,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         sysMsg, 256, NULL );

  // Trim the end of the line and terminate it with a null
  p = sysMsg;
  while( ( *p > 31 ) || ( *p == 9 ) )
    ++p;
  do { *p-- = 0; } while( ( p >= sysMsg ) &&
                          ( ( *p == '.' ) || ( *p < 33 ) ) );

  // Display the message
  printf("\n  WARNING: Operation failed with error %d (%s)", eNum, sysMsg );
}

void ListProcess(int argc, char** argv) {
    if (argc > 2) {
        _WARNING_MANY_ARG_("list");
    }
    int searchAllProcess = 0;
    if (argc == 2) {
        if (!strcmp(argv[1], "all")) {
            searchAllProcess = 1;
        }
        else {
            printf("Invalid argument for \'%s\'. Try \'%s all\'\n", argv[0], argv[0]);
            return;
        }
    }
    HANDLE hProcess;
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        printError();
        return;
    }
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        printError(); // show cause of failure
        CloseHandle( hProcessSnap );          // clean the snapshot object
        return;
    }
    // Now walk the snapshot of processes, and
    // display information about each process in turn
    if (searchAllProcess == 0) {
        do {
            hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
            if (hProcess != NULL) {
                printf( "\nPROCESS NAME:  %s", pe32.szExeFile );
                printf( "\n  Process ID        = %d", pe32.th32ProcessID );
                printf( "\n  Thread count      = %d",   pe32.cntThreads );
            }
        } while( Process32Next( hProcessSnap, &pe32 ) );
    }
    else {
        do {
            printf( "\nPROCESS NAME:  %s", pe32.szExeFile );
            printf( "\n  Process ID        = %d", pe32.th32ProcessID );
            printf( "\n  Thread count      = %d",   pe32.cntThreads );
        } while( Process32Next( hProcessSnap, &pe32 ) );
    }
    CloseHandle( hProcessSnap );
}

PROCESS SearchProcessName(char* processName) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    PROCESS p = {"noname", 0, 0};
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        printError();
        return p;
    }
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        printError(); // show cause of failure
        CloseHandle( hProcessSnap );          // clean the snapshot object
        return p;
    }
    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do {
        if (strcmp(pe32.szExeFile, processName) == 0) {
            strcpy(p.name, pe32.szExeFile);
            p.processID = pe32.th32ProcessID;
            p.threadCount = pe32.cntThreads;
            return p;
        }
    } while( Process32Next( hProcessSnap, &pe32 ) );
    CloseHandle( hProcessSnap );
    return p;
}

PROCESS SearchProcessID(int processID) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    PROCESS p = {"noname", 0, 0};
    // Take a snapshot of all processes in the system.
    hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if( hProcessSnap == INVALID_HANDLE_VALUE )
    {
        printError();
        return p;
    }
    // Set the size of the structure before using it.
    pe32.dwSize = sizeof( PROCESSENTRY32 );
    // Retrieve information about the first process,
    // and exit if unsuccessful
    if( !Process32First( hProcessSnap, &pe32 ) )
    {
        printError(); // show cause of failure
        CloseHandle( hProcessSnap );          // clean the snapshot object
        return p;
    }
    // Now walk the snapshot of processes, and
    // display information about each process in turn
    do {
        if (pe32.th32ProcessID == processID) {
            strcpy(p.name, pe32.szExeFile);
            p.processID = pe32.th32ProcessID;
            p.threadCount = pe32.cntThreads;
            return p;
        }
    } while( Process32Next( hProcessSnap, &pe32 ) );
    CloseHandle( hProcessSnap );
    return p;
}

void SearchProcess(int argc, char** argv) {  
    if (argc > 3) {
        _WARNING_MANY_ARG_("search");
    }
    if (argc < 2) {
        _WARNING_FEW_ARG_("search");
    }
    if (argc == 2) {
        char* processName = argv[1];
        PROCESS p = SearchProcessName(processName);    
        if (p.threadCount == 0) {
            printf("Process not found\n");
        }
        else {
            printf("\nPROCESS NAME:  %s\n", p.name );
            printf("  Process ID        = %d\n", p.processID );
            printf("  Thread count      = %d\n", p.threadCount );
        }
    }
    else if (argc ==3) {
        if (!strcmp(argv[1], "pid")) {
            int processID = atoi(argv[2]);
            PROCESS p = SearchProcessID(processID);
            if (p.threadCount == 0) {
                printf("Process not found\n");
            }
            else {
                printf("\nPROCESS NAME:  %s\n", p.name );
                printf("  Process ID        = %d\n", p.processID );
                printf("  Thread count      = %d\n", p.threadCount );
            }
        }
        else{
            printf("Invalid argument for \'%s\'. Try \'%s pid process_ID\'\n", argv[0], argv[0]);
            return;
        }
    }
}

void KillProcess(int argc, char** argv) {  
    if (argc < 2) {
        _WARNING_FEW_ARG_("kill");
    }
    if (argc > 3) {
        _WARNING_MANY_ARG_("kill");
    }
    //Kill by name
    if (argc == 2) {
        char* processName = argv[1];
        PROCESS p = SearchProcessName(argv[1]);
        if (p.threadCount == 0) {
            printf("Process not found\n");
            return;
        }
        HANDLE hProcess = OpenProcess( PROCESS_TERMINATE, TRUE, p.processID );
        if (hProcess == NULL) printError();
        else {
            printf("Process terminated\n");
            TerminateProcess(hProcess, 0);
            CloseHandle(hProcess);
        }
    }
    //Kill by process ID
    else if (argc == 3) {
        if (!strcmp(argv[1], "pid")) {
            int processID = atoi(argv[2]);
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, TRUE, processID );
            if (hProcess == NULL) printError();
            else {
                printf("Process terminated\n");
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
            }
        }
        else {
            printf("Invalid argument for \'%s\'. Try \'%s pid process_ID\'\n", argv[0], argv[0]);
            return;
        }        
    }   
}

void SuspendProcessID(int processID) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (hProcess == NULL) {
        printError();
        return;
    }
    NtSuspendProcess pfnNtSuspendProcess = 
        (NtSuspendProcess)GetProcAddress(GetModuleHandle("ntdll"), "NtSuspendProcess");
    pfnNtSuspendProcess(hProcess);
    printf("Process Stopped\n");
    CloseHandle(hProcess);
}

void StopProcess(int argc, char** argv) {
    if (argc < 2) {
        _WARNING_FEW_ARG_("stop");
    }
    if (argc > 3) {
        _WARNING_MANY_ARG_("stop");
    }
    if (argc == 2) {
        PROCESS p = SearchProcessName(argv[1]);
        if (p.threadCount == 0) {
            printf("Process not found\n");
        }
        else {
            SuspendProcessID(p.processID);
        }
    }
    else if (argc ==3) {
        if (!strcmp(argv[1], "pid")) {
            int processID = atoi(argv[2]);
            SuspendProcessID(processID);
        }
        else {
            printf("Invalid argument for \'%s\'. Try \'%s pid process_ID\'\n", argv[0], argv[0]);
            return;
        }
    }
}

void ResumeProcessID(int processID) {
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (hProcess == NULL) {
        printError();
        return;
    }
    NtResumeProcess pfnNtResumeProcess = 
        (NtResumeProcess)GetProcAddress(GetModuleHandle("ntdll"), "NtResumeProcess");
    pfnNtResumeProcess(hProcess);
    printf("Process Resumed\n");
    CloseHandle(hProcess);
}

void ResumeProcess(int argc, char** argv) {
    if (argc < 2) {
        _WARNING_FEW_ARG_("resume");
    }
    if (argc > 3) {
        _WARNING_MANY_ARG_("resume");
    }
    if (argc == 2) {
        PROCESS p = SearchProcessName(argv[1]);
        if (p.threadCount == 0) {
            printf("Process not found\n");
        }
        else {
            ResumeProcessID(p.processID);
        }
    }
    else if (argc ==3) {
        if (!strcmp(argv[1], "pid")) {
            int processID = atoi(argv[2]);
            ResumeProcessID(processID);
        }
        else {
            printf("Invalid argument for \'%s\'. Try \'%s pid process_ID\'\n", argv[0], argv[0]);
            return;
        }
    }
}

BOOL WINAPI CtrlHandler(DWORD fdwCtrlType) {
    switch (fdwCtrlType) {
        // Handle the CTRL-C signal. 
        case CTRL_C_EVENT:
            TerminateProcess(piPointer->hProcess, 0);
            CloseHandle(piPointer->hProcess);
            CloseHandle(piPointer->hThread);
            return TRUE;
        default:
            return FALSE;

    }
}

void CreateProcessBackground(int argc, char** argv, char* command){
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    ZeroMemory( &pi, sizeof(pi) );
    if(!CreateProcess(  NULL, 
                    command, 
                    NULL, 
                    NULL, 
                    FALSE, 
                    CREATE_NEW_CONSOLE, 
                    NULL, 
                    NULL, 
                    &si, 
                    &pi)) {
        printf("\'%s\' is not recognized as an internal or external command, operable program or batch file.\n", argv[0]);
    }
    
}
void CreateProcessForeground(int argc, char** argv, char* command){
    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    ZeroMemory( &pi, sizeof(pi) );
    if(!CreateProcess(  NULL, 
                    command, 
                    NULL, 
                    NULL, 
                    FALSE, 
                    NORMAL_PRIORITY_CLASS, 
                    NULL, 
                    NULL, 
                    &si, 
                    &pi)) {
        printf("\'%s\' is not recognized as an internal or external command, operable program or batch file.\n", argv[0]);
    }
    else{
        piPointer = &pi;
        SetConsoleCtrlHandler((PHANDLER_ROUTINE) CtrlHandler, TRUE );
        WaitForSingleObject(pi.hProcess, INFINITE);
    }
}

