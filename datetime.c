/* localtime example */
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include "macro.h"
#include "datetime.h"

char month[13][10] = {"0", "January", "February", "March", "April",
					  "May", "June", "July", "August", "September", 
					  "October", "November", "December"};
char dayOfWeek[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday",
						 "Thusday", "Friday", "Saturday"};

void SetDate(int argc, char** argv)
{
	if(argc <= 1)
		_WARNING_FEW_ARG_("setdate");
	if(argc > 2)
		_WARNING_MANY_ARG_("setdate");
		
	SYSTEMTIME newDate, oldDate;
	GetLocalTime(&oldDate);
	newDate = oldDate;
	int numberOfDigit = 0, flag = 1, dateCount = 0;
	WORD dateTemp = 0, i = 0;
	int len = strlen(argv[argc - 1]);
	char *str = (char*) malloc ((len + 2) * sizeof(char));
	strcpy(str, argv[argc - 1]);
	str[len] = '/';
	str[len + 1] = '\0';
	
	while(str[i] != '\0')
	{
		if(isdigit(str[i]))
		{
			dateTemp = str[i] - 48 + dateTemp * 10;
			numberOfDigit++;
		}
		else if(str[i] = '/')
		{
			dateCount++;
			if(dateCount == 1 && dateTemp <= 31)
			{
				if(numberOfDigit > 2 || numberOfDigit < 1)
					_TERMINATE_
				newDate.wDay = dateTemp;
			}
			else if(dateCount == 2 && dateTemp <= 12)
			{
				if(numberOfDigit > 2 || numberOfDigit < 1)
					_TERMINATE_
				switch(dateTemp)
				{
					case 1:
					case 3:
					case 5:
					case 7:
					case 8:
					case 10:
					case 12:
						break;
					default:
						if((newDate.wDay == 31) || (dateTemp == 2 && newDate.wDay > 29))
      						_TERMINATE_
				}
				newDate.wMonth = dateTemp;
			}
			else if(dateCount == 3 && dateTemp > MINYEAR && dateTemp < MAXYEAR)
			{
				if(_CHECK_LEAP_YEAR_(newDate.wDay, newDate.wMonth, dateTemp)
				   || numberOfDigit > 5 || numberOfDigit < 4)
					_TERMINATE_
				newDate.wYear = dateTemp;
			}
			else
				_TERMINATE_
			dateTemp = 0;
			numberOfDigit = 0;
		}
		else
			_TERMINATE_
		i++;
	}
	
	if(flag != 0 && dateCount == 3)
	{
		if(!SetLocalTime(&newDate))
            {
                printf("A required privilege is not held by the client.\n");
            }
	}
	else
	{
		printf("The system cannot accept the date entered.\n");
	}
}

void SetTime(int argc, char** argv)
{
	if(argc <= 1)
		_WARNING_FEW_ARG_("settime");
	if(argc > 2)
		_WARNING_MANY_ARG_("settime");
		
	SYSTEMTIME time;
	GetLocalTime(&time);
	int numberOfDigit = 0, flag = 1, timeCount = 0;
	WORD timeTemp = 0, i = 0;
	int len = strlen(argv[argc - 1]);
	char *str = (char*) malloc ((len + 2) * sizeof(char));
	strcpy(str, argv[argc - 1]);
	str[len] = '/';
	str[len + 1] = '\0';
	
	while(str[i] != '\0')
	{
		if(isdigit(str[i]))
		{
			timeTemp = str[i] - '0' + timeTemp * 10;
			numberOfDigit++;
		}
		else if(str[i] = ':')
		{
			timeCount++;
			if(timeCount == 1 && timeTemp <= 24)
			{
				if(numberOfDigit > 2 || numberOfDigit < 1)
					_TERMINATE_
				time.wHour = timeTemp;
			}
			else if(timeCount == 2 && timeTemp <= 60)
			{
				if(numberOfDigit > 2 || numberOfDigit < 1)
					_TERMINATE_
				time.wMinute = timeTemp;
			}
			else if(timeCount == 3 && timeTemp <= 60)
			{
				if(numberOfDigit > 2 || numberOfDigit < 1)
					_TERMINATE_
				time.wSecond = timeTemp;
			}
			else
				_TERMINATE_
			timeTemp = 0;
			numberOfDigit = 0;
		}
		else
			_TERMINATE_
		i++;
	}
	
	if(flag != 0 && timeCount == 3)
	{
		if(!SetLocalTime(&time))
            {
                printf("A required privilege is not held by the client.\n");
            }
	}
	else
	{
		printf("The system cannot accept the time entered.\n");
	}
}

void GetTime(int argc)
{
	if(argc > 1)
		_WARNING_MANY_ARG_("time");
		
	SYSTEMTIME time;
	GetLocalTime(&time);
	printf("%s, %s %d, %d, %d:%d:%d\n", dayOfWeek[time.wDayOfWeek], month[time.wMonth], time.wDay, time.wYear, time.wHour, time.wMinute, time.wSecond);
}
