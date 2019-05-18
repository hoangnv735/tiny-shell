#include "run.h"
#include "std.h"
#include "bat.h"

char command[MAX_PATH];
int argc = 0;
char** argv = NULL;

//Run command
void RunCommand(char* inputString) {
    //Standardlize input string
    FormatString(inputString);
    if (inputString[0] == '\0') {
        return;
    }
    // store formated input string in variable command
    strcpy(command, inputString);
    // After spit, inputstring will be tear apart, separated by NULL character
    SplitCommand(inputString, &argc, &argv);

    // if argv[0] is a batfile
    if (CheckBatFile(argv[0])) {
        ExecuteBatFile(argv[0]);
    }
    // not a batfile
    else {
        // append ".bat" to the end of filename
        int length = strlen(argv[0]);
        char filename[length + 4];
        strcpy(filename, argv[0]);
        strcat(filename, ".bat");
        // if file exists
        if (PathFileExists(filename)) {
            ExecuteBatFile(filename);
        }
        // file do not exits
        else {
            // execute command 
            ExecuteCommand(argc, argv, command);
        }
    }
    // free memory
    // (there is dynamic memory request in SplitCommand function)
    DeleteCommand(&argc, &argv);
}