#ifndef BAT_H
#define BAT_H

#include <shlwapi.h>
#include <string.h>
#include <stdlib.h>

int CheckBatFile(char* filename);
void ExecuteBatFile(char* filename);

#endif //BAT_H