#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "Macro.h"
#include "Path.h"

// List all environment variables
void Path(int argc) {
	if(argc < 1)
		_WARNING_FEW_ARG_("path")
	if(argc >= 2)
		_WARNING_MANY_ARG_("path")
	LPTCH lpEnvVar;
	// Get environment 
	lpEnvVar = GetEnvironmentStrings();
	if(lpEnvVar == NULL) {
        printf("Cannot find the pointer to the environment block of the current process");
        return;
    }
    while(*lpEnvVar) {
    	printf("%s \n", lpEnvVar);
    	lpEnvVar += lstrlen(lpEnvVar) + 1;
    }
    FreeEnvironmentStrings(lpEnvVar);
}

// Add environent variable
void AddPath(int argc, char **argv)
{
	if(argc <= 2)
		_WARNING_FEW_ARG_("addpath")
	if(argc > 3)
		_WARNING_MANY_ARG_("addpath")
	if(SetEnvironmentVariable(argv[1], argv[2]))
		Path(1);
	else
		printf("SetEnvironmentVariable failed (%lu)\n", GetLastError());
}
