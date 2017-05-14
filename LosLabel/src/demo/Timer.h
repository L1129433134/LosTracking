//
// Created by lup on 17-5-14.
//

#ifndef LOSLABEL_TIMER_H
#define LOSLABEL_TIMER_H

#include <time.h>
#include <chrono>
#include <vector>
#include <string>

namespace
{
    const std::vector<std::string> monthName = {
           "error!",
           "January",
           "February",
           "March",
           "April",
           "May",
           "June",
           "July",
           "August",
           "September",
           "October",
           "November",
           "December"
    };

    const std::vector<std::string> wdayName = {
            "Sunday",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
    };

    const int nanosPreSeconds =  1000000000;
}

class Timer
{
public:
    Timer(int _timeZone = 8, int _clockPreSec = 1000) : timeZone(_timeZone), nanosPreClock(nanosPreSeconds / _clockPreSec) {}
    ~Timer() {}

    void timingStart();
    double timingStop();


    void setTimeZone(const int _timeZone) {timeZone = _timeZone;}
    int getTimeZone() { return timeZone;}

private:
    void initTime();
    void setTime();

public:
    int year;       /* Year*/
    int month;      /* Month.	[1-12] */
    int day;        /* Day.		[1-31] */
    int hour;       /* Hours.	[0-23] */
    int minute;     /* Minutes.	[0-59] */
    int second;     /* Seconds.	[0-60] (1 leap second) */

    int wday;       /* Day of week.	[0-6] */

    int timeZone;   /* time zone.[-12 - +12]*/

private:
    tm Ctime;
    time_t seconds;                   /* Seconds since the Epoch.  */
    bool leapYear = false;
    std::vector<int> monthDayNums{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    std::chrono::system_clock::time_point clockTime;
    int nanosPreClock;
};

#endif //LOSLABEL_TIMER_H
