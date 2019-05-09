#include "run.h"
#include "std.h"
#include "bat.h"

char command[MAX_PATH];
int argc = 0;
char** argv = NULL;

void RunCommand(char* inputString) {
    FormatString(inputString);
    if (inputString[0] == '\0') {
        return;
    }
    strcpy(command, inputString);
    SplitCommand(inputString, &argc, &argv);
    if (CheckBatFile(argv[0])) {
        ExecuteBatFile(argv[0]);
    }
    else {
        int length = strlen(argv[0]);
        char filename[length + 4];
        strcpy(filename, argv[0]);
        strcat(filename, ".bat");
        if (PathFileExists(filename)) {
            ExecuteBatFile(filename);
        }
        else {
            ExecuteCommand(argc, argv, command);
        }
    }
    DeleteCommand(&argc, &argv);
}