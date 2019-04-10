#ifndef DATETIME_H
#define DATETIME_H

#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include "Macro.h"

#define MAXYEAR 30827
#define MINYEAR 1601

#define _CHECK_LEAP_YEAR_(day, month, year)												   \
	(((!(year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) && month == 2 && day >= 29)\
	|| (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2 && day >= 30)
#define _TERMINATE_ \
{                   \
    flag = 0;       \
    break;          \
}

void GetTime(int argc);
void SetTime(int argc, char** argv);
void SetDate(int argc, char** argv);

#endif //DATETIME_H
