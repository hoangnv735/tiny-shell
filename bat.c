#include "bat.h"
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
    
}