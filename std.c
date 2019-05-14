#include "std.h"
#include "datetime.h"
#include "shell.h"
#include "help.h"
#include "path.h"
#include "process.h"
#include "directory.h"

#define SIZE_COMMANDS 14
const char* COMMANDS[] = {"addpath", "cls", "dir", "exit", "help",
                    "kill", "list", "path", "resume", "search",
                    "setdate", "settime", "stop", "time"};
enum COMMAND_INDEX {ADDPATH, CLS, DIR, EXIT, HELP,
                    KILL, LIST, PATH, RESUME, SEARCH,
                    SETDATE, SETTIME, STOP, TIME};
/*Standardize a string
    recieve a pointer of first character
    return the same pointer without changing value*/
char* FormatString(char* string) {
    int i = 0;
    int j = 0;
    int len = strlen(string);
    while (string[j] == ' ') {
        j++;
    }
    if (string[j] == '\0') {
        string[i] = '\0';
        return string;
    }
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
    if (string[i] == ' ') {
        string[i] = '\0';
    }
    else {
        string[i + 1] = '\0';
    }
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

void ReadCommand(char* inputString, int length) {
    fflush(stdin);
    fgets(inputString, length+1, stdin);
    //gets(inputString);
    inputString[strlen(inputString) - 1] = '\0';
}

void SplitCommand(char* inputString, int* argcPointer, char*** argvPointer){
    int spaceCounter = 0;
    int length = strlen(inputString);
    for(int i = 0; i < length; i++) {
        if (inputString[i] == ' ') {
            spaceCounter++;
        }
    }
    *argcPointer = spaceCounter + 1;

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

void DeleteCommand(int* argcPointer, char*** argvPointer){
    free(*argvPointer);
}

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

char* ToLower(char* s) {
    int length = strlen(s);
    for (int i = 0; i < length; i++) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            s[i] = s[i] + (char)32 ;
        }
    }
    return s;
}

void ExecuteCommand(int argc, char** argv, char* command){
    char temp[512];
    strcpy(temp, argv[0]);
    int commandIndex = FindCommand(ToLower(temp));
    if (commandIndex == -1) {
        if (!strcmp(argv[argc - 1], "&")) {
            command[strlen(command) - 2] = '\0';
            CreateProcessForeground(argc, argv, command);
        }
        else {            
            CreateProcessBackground(argc, argv, command);
        }
    }
    else {
        switch(commandIndex) {
            case ADDPATH:
                AddPath(argc, argv);
                break;
            case CLS:
                ClearScreen(argc);
                break;
            case DIR:
                DirectoryCommand(argc, argv);
                break;
            case EXIT:
                ExitShell(argc);
                break;
            case HELP:
                HelpShell(argc);
                break;
            case KILL:
                KillProcess(argc, argv);
                break;
            case LIST:
                ListProcess(argc, argv);
                break;
            case PATH:
                Path(argc);
                break;
            case RESUME:
                ResumeProcess(argc, argv);
                break;
            case SEARCH:
                SearchProcess(argc, argv);
                break;
            case SETDATE:
                SetDate(argc, argv);
                break;
            case SETTIME:
                SetTime(argc, argv);
                break;
            case STOP:
                StopProcess(argc, argv);
                break;
            case TIME:
                GetTime(argc);
                break;
        }
    }
}
