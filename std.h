#ifndef STD_H
#define STD_H

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

char* FormatString(char* string);   
void PrintCurrentDirectory();
void ReadCommand(char* inputString, int length);
void SplitCommand(char* inputString, int* argcPointer, char*** argvPointer);
void DeleteCommand(int* argcPointer, char*** argvPointer);
void ExecuteCommand(int argc, char** argv, char* command);


#endif //STD_H