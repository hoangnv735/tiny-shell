#include "bat.h"
#include "std.h"
#include "run.h"

int CheckBatFile(char* filename){
    int length = strlen(filename); 
    if (length > 4 &&
        filename[length - 4] == '.' &&
        filename[length - 3] == 'b' && 
        filename[length - 2] == 'a' &&
        filename[length - 1] == 't') {
            return 1;
    }
    return 0;
}

void ExecuteBatFile(char* filename) {
    FILE * f = fopen(filename, "r");
    if (!f) {
        printf("Can not open file %s\n", filename);
        return;
    }
    printf("Executing %s\n", filename);
    char inputString[MAX_PATH];
    fflush(stdin);
    while (fgets(inputString, MAX_PATH + 1, f)) {
        //inputString[strlen(inputString) - 1] = '\0';
        fflush(stdin);
        PrintCurrentDirectory();
        printf("%s\n", inputString);
        RunCommand(inputString);
    }
    fclose(f);
}