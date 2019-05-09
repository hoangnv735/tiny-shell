#include "directory.h"
#include "macro.h"

void DirectoryCommand(int argc, char** argv) {
    if (argc > 1){
        _WARNING_MANY_ARG_("dir");
    }
    
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);
    printf("\n Directory of %s\n\n", currentDirectory);

    WIN32_FIND_DATA findData;
    LARGE_INTEGER fileSize;
    SYSTEMTIME sysTime;
    SYSTEMTIME localTime;
    long long sumFileSize = 0;
    int fileCount = 0, directoryCount = 0;
    //strcat(currentDirectory, "\\*");
    char dir[MAX_PATH];
    strcpy(dir, currentDirectory);
    strcat(dir, "\\*");
    
    HANDLE hFind = INVALID_HANDLE_VALUE;

    hFind = FindFirstFile(dir, &findData);

    do {
        FileTimeToSystemTime(&findData.ftLastWriteTime, &sysTime);
        SystemTimeToTzSpecificLocalTime(NULL, &sysTime, &localTime);
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            directoryCount++;
            printf("%02u/%02u/%04u  %02u:%02u    <DIR>%-10s %s\n",
                    localTime.wDay, localTime.wMonth, localTime.wYear, 
                    localTime.wHour, localTime.wMinute,
                    " ", findData.cFileName);
        } else {
            fileCount++;
            fileSize.LowPart = findData.nFileSizeLow;
            fileSize.HighPart = findData.nFileSizeHigh;
            sumFileSize += fileSize.QuadPart;
            printf("%02u/%02u/%04u  %02u:%02u         %10d ",
                    localTime.wDay, localTime.wMonth, localTime.wYear,
                    localTime.wHour, localTime.wMinute, 
                    fileSize);
            printf("%s\n", findData.cFileName);
        }
    } while (FindNextFile(hFind, &findData) != 0);
    printf("%14d File(s) %13d bytes\n", fileCount, sumFileSize);
    printf("%14d Dir(s)\n", directoryCount);
    FindClose(hFind);
}