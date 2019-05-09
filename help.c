#include "help.h"
#include "macro.h"


void HelpShell(int argc){
    if (argc > 1) {
        _WARNING_MANY_ARG_("help");
    }

    puts("\nInformation about available commands:");

    printf("%-10s  Add a path to environment variable.\n", "ADDPATH");
    printf("%-10s  Clear the screen.\n", "CLS");
    printf("%-10s  Displays a list of files and subdirectories in a directory.\n", "DIR");
    printf("%-10s  Quits the tiny-shell.exe program (command interpreter).\n", "EXIT");
    printf("%-10s  Provides help information for shell commands.\n", "HELP");
    printf("%-10s  Kill a process.\n", "KILL");
    printf("%-10s  List of process.\n", "LIST");
    printf("%-10s  Displays or sets a search path for executable iles.\n", "PATH");
    printf("%-10s  Resume a process that is stopping.\n", "RESUME");
    printf("%-10s  Search for a running process.\n", "SEARCH");
    printf("%-10s  Sets the system date dd/mm/yyyy.\n", "SETDATE");
    printf("%-10s  Set the system time hh:mm:ss.\n", "SETTIME");
    printf("%-10s  Displays the system time.\n", "TIME");
}
