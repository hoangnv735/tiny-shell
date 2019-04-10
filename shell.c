#include "shell.h"
#include "macro.h"

void ExitShell(int argc){
    if (argc > 1) {
        _WARNING_MANY_ARG_("exit"); 
    }
    else {
        exit(0);
    }
}

void ClearScreen(int argc){
    if (argc > 1) {
        _WARNING_MANY_ARG_("cls"); 
    }
    else {
        system("cls");
    }
}