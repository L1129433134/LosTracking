//
// Created by lup on 17-5-14.
//

#ifndef LOSLABEL_TIMER_H
#define LOSLABEL_TIMER_H

#include <time.h>

class Timer
{
public:
    Timer() {}
    ~Timer() {}

    void timingStart();
    long timingCurrent();
    long timingStop();

    void test();

public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    int yday;
    int wday;

private:

};


#endif //LOSLABEL_TIMER_H
