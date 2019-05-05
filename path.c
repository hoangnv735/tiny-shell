#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "Macro.h"
#include "Path.h"

void Path()
{
	/*Dua ra cac bien moi truong cua tien trinh hien tai
	  su dung ham WINAPI GetEnvironmentStrings*/
	LPTCH lpEnvVar;
	lpEnvVar = GetEnvironmentStrings();
	if(lpEnvVar == NULL)
    {
        printf("Cannot find the pointer to the environment block of the current process");
        return;
    }
    while(*lpEnvVar)
    {
    	_tprintf(_T("%s \n"), lpEnvVar);
    	lpEnvVar += lstrlen(lpEnvVar) + 1;
    }
    FreeEnvironmentStrings(lpEnvVar);
}

void AddPath(int argc, char **argv)
{
	/*Them 1 bien moi truong
	  tham so dau vao gom ten bien moi truong va noi dung*/
	if(argc <= 2)
		_WARNING_FEW_ARG_("addpath")
	if(argc > 3)
		_WARNING_MANY_ARG_("addpath")
	if(SetEnvironmentVariable(argv[1], argv[2]))
		Path();
	else
		printf("SetEnvironmentVariable failed (%lu)\n", GetLastError());
}
