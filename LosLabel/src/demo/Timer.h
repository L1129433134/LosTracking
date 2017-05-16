//
// Created by lup on 17-5-14.
//

#ifndef LOSLABEL_TIMER_H
#define LOSLABEL_TIMER_H

#include <time.h>
#include <chrono>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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
}

class Timer
{
public:
    Timer(int _clockPreSec = 1000) : nanosPreClock(nanosPreSeconds / _clockPreSec)
    {
        clockTime = std::chrono::system_clock::now();
    }
    ~Timer() {}

    void reinit()
    {
        notes.clear();
        clockTime = std::chrono::system_clock::now();
    }

    double stop() const
    {
        return static_cast<double>((std::chrono::system_clock::now() - clockTime).count()) / nanosPreClock;
    }

    double record()
    {
        double note = static_cast<double>((std::chrono::system_clock::now() - clockTime).count()) / nanosPreClock;
        notes.push_back(note);
        return note;
    }

    std::vector<double> getNotes() const
    {
        return notes;
    }

private:
    std::chrono::system_clock::time_point clockTime;
    int nanosPreClock;

    std::vector<double> notes;
    static const int nanosPreSeconds =  1000000000;
};

class DateAndTime
{
public:
    DateAndTime(int _timeZone = 8) : timeZone(_timeZone)
    {
        initTime();
    }
    ~DateAndTime() {}

    void reinit(int _timeZone = 8)
    {
        timeZone = _timeZone;
        initTime();
    }

    std::string getString() const
    {
        std::stringstream ss;
        ss << wdayName[wday] << "_" << monthName[month]<<"_"<<day<<"_"<<hour<<"-"<<minute<<"-"<<second<<"_"<<year;
        return ss.str();
    }

    void printFormat() const
    {
        char *tmp = asctime(&Ctime);
        std::cout<<tmp;
    }

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
};

#endif //LOSLABEL_TIMER_H
