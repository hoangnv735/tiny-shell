#include "std.h"
#include "datetime.h"
#include "shell.h"
#include "help.h"
#include "path.h"
#include "process.h"
#include "directory.h"

#define SIZE_COMMANDS 14
// The command list
const char* COMMANDS[] = {"addpath", "cls", "dir", "exit", "help",
                    "kill", "list", "path", "resume", "search",
                    "setdate", "settime", "stop", "time"};
enum COMMAND_INDEX {ADDPATH, CLS, DIR, EXIT, HELP,
                    KILL, LIST, PATH, RESUME, SEARCH,
                    SETDATE, SETTIME, STOP, TIME};
/*Standardlize a string
    recieve a pointer of first character
    return the same pointer without changing value*/
char* FormatString(char* string) {
    int i = 0;
    int j = 0;
    int len = strlen(string);
    // Delete space at the begin of command
    while (string[j] == ' ') {
        j++;
    }
    // If end string
    if (string[j] == '\0') {
        string[i] = '\0';
        return string;
    }
    // Copy character
    string[i] = string[j];
    for(int k = j + 1; k < len; k++) {
        if (string[k] == ' ') {
            if (string[i] != ' ') {
                i++;
                string[i] = ' ';
            }
        }
        else {
            i++;
            string[i] = string[k];
        }
    }
    // Delete space at the end of command (after copy)
    if (string[i] == ' ') {
        string[i] = '\0';
    }
    else {
        string[i + 1] = '\0';
    }
    // Delete \n and \t at the end of command (after copy)
    int last = strlen(string) - 1;
    if (string[last] == '\n' || string[last] == '\t') {
        do {
            last--;
        } while (string[last] == '\n' || string[last] == '\t');
        string[last + 1] = '\0';
    }
    return string;
}

/*Print current directory */
void PrintCurrentDirectory() {
    char currentDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDirectory);
    printf("\n%s>", currentDirectory);
}

//Read command 
void ReadCommand(char* inputString, int length) {
    fflush(stdin);
    fgets(inputString, length+1, stdin);
    //gets(inputString);
    inputString[strlen(inputString) - 1] = '\0';
}

// Tear input string apart, reaparated by NULL character, 
// Argv store addresses of argument
void SplitCommand(char* inputString, int* argcPointer, char*** argvPointer){
    int spaceCounter = 0;
    int length = strlen(inputString);
    for(int i = 0; i < length; i++) {
        if (inputString[i] == ' ') {
            spaceCounter++;
        }
    }
    *argcPointer = spaceCounter + 1;

    // this is why we need DeleteCommand after Runcommand
    *argvPointer = (char**) malloc((*argcPointer) * sizeof(char*));
    int mark = 0;
    spaceCounter = 0;
    for(int i = 0; i < length; i++) {
        if (inputString[i] == ' ') {
            (*argvPointer)[spaceCounter] = inputString + mark;
            inputString[i] = '\0';
            mark = i + 1;
            spaceCounter++;
        }
    }
    (*argvPointer)[spaceCounter] = inputString + mark;
}

// Free memory oof argv
void DeleteCommand(int* argcPointer, char*** argvPointer){
    free(*argvPointer);
}

// Find command in COMMANDS (a list of commands) using binary search
int FindCommand(char* command) {
    int left = 0;
    int right = SIZE_COMMANDS - 1;
    int mid;
    int temp;
    while (left <= right) {
        mid = (left + right) / 2;
        temp = strcmp(command, COMMANDS[mid]);
        if (temp == 0) {
            return mid;
        }
        if (temp < 0) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

// Convert fisrt argument to lower
char* ToLower(char* s) {
    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            s[i] = s[i] + (char)32 ;
        }
    }
    return s;
}

//Execute command
void ExecuteCommand(int argc, char** argv, char* command){
    char temp[512];
    strcpy(temp, argv[0]);

    // Convert first argument to lower
    int commandIndex = FindCommand(ToLower(temp));
    // if not a build-in command in command list
    if (commandIndex == -1) {
        // is there is "&" at the end of command
        if (!strcmp(argv[argc - 1], "&")) {
            // detele "&"
            command[strlen(command) - 2] = '\0';
            // Run in foreground mode
            CreateProcessForeground(argc, argv, command);
        }
        // there is not "&"
        else {            
            // Run in background mode
            CreateProcessBackground(argc, argv, command);
        }
    }
    // It is a built-in command in commmand list
    else {
        switch(commandIndex) {
            // Add environment variable
            case ADDPATH:
                AddPath(argc, argv);
                break;
            // Clear screen
            case CLS:
                ClearScreen(argc);
                break;
            // List all file in directory
            case DIR:
                DirectoryCommand(argc, argv);
                break;
            // Exit shell
            case EXIT:
                ExitShell(argc);
                break;
            // Print help
            case HELP:
                HelpShell(argc);
                break;
            // Terminate a process
            case KILL:
                KillProcess(argc, argv);
                break;
            // List all process
            case LIST:
                ListProcess(argc, argv);
                break;
            // Print out all evironment variable
            case PATH:
                Path(argc);
                break;
            // Resume a process
            case RESUME:
                ResumeProcess(argc, argv);
                break;
            // Search for a process
            case SEARCH:
                SearchProcess(argc, argv);
                break;
            // Set date 
            case SETDATE:
                SetDate(argc, argv);
                break;
            // Set time
            case SETTIME:
                SetTime(argc, argv);
                break;
            // Suspend a process
            case STOP:
                StopProcess(argc, argv);
                break;
            // Show time and date
            case TIME:
                GetTime(argc);
                break;
        }
    }
}
