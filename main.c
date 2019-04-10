#include "std.h"
#include "bat.h"
#include <shlwapi.h>
#include <string.h>
#include <stdlib.h>

int main() {
    system("cls");
    printf("tiny-shell v1.0\n");
    printf("HoangNV, PhucVH, NhungNT \n");
    printf("20182 Dai hoc Bach khoa Ha Noi\n");
    
    char inputString[MAX_PATH];

    while (1) {
        int argc = 0;
        char** argv = NULL;

        PrintCurrentDirectory();
        ReadCommand(inputString, MAX_PATH);
        FormatString(inputString);
        if (inputString[0] == '\0') {
            continue;
        }
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
                ExecuteCommand(argc, argv);
            }
        }
        DeleteCommand(&argc, &argv);
    }
    return 0;
}