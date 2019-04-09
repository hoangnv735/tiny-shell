#include "std.h"
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
    fgets(inputString, length, stdin);
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
        if (inputString[0] == ' ') {
            *(argvPointer[spaceCounter]) = &(inputString[mark]);
            mark = i + 1;
            spaceCounter++;
        }
    }
    *(argvPointer[spaceCounter]) = &(inputString[mark]);
}

void DeleteCommand(int* argcPointer, char*** argvPointer){
    free(*argvPointer);
}