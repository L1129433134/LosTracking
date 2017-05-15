//
// Created by lup on 17-5-14.
//

#include "Timer.h"
#include <iostream>

//---------------------DateAndTime--------------------------------------------------------------------------------------
void DateAndTime::initTime()
{
    seconds = time(NULL);
    if (timeZone == 8)
    {
        Ctime = *localtime(&seconds);
    }
    else
    {
        Ctime = *gmtime(&seconds);
    }

    setTime();
}

void DateAndTime::setTime()
{
    year = Ctime.tm_year + 1900;
    month = Ctime.tm_mon + 1;
    day = Ctime.tm_mday;
    wday = Ctime.tm_wday;
    hour = Ctime.tm_hour;
    minute = Ctime.tm_min;
    second = Ctime.tm_sec;

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        leapYear = true;
        monthDayNums[2] += 1;
    }

    if (timeZone != 0 && timeZone != 8)
    {
        hour += timeZone;

        if (hour > 23)
        {
            hour -= 24;

            if ((++wday) > 6)
            {
                wday = 0;
            }

            if ((++day) > monthDayNums[month])
            {
                day = 1;

                if ((++month) > 12)
                {
                    month =1;
                    year += 1;
                }
            }
        }
        else if (hour < 0)
        {
            hour += 24;

            if((--wday) < 0)
            {
                wday = 6;
            }

            if ((--day) < 1)
            {
                if (month == 1)
                {
                    year -=1;
                    month = 12;
                    day = monthDayNums[month];
                }
                else
                {
                    month -= 1;
                    day = monthDayNums[month];
                }
            }
        }
    }
}
