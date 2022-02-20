#ifndef DATE_H
#define DATE_H

#include <ctime>

// Date -> Day of the Year 
struct Date {
    Date() {
        time_t timer;
        tm* time = localtime(&timer);

        this->day = time->tm_mday;
        this->month = time->tm_mon;
        this->year = time->tm_year + 1900;
        this->dayOfWeek = time->tm_wday;

        // ~timer();
    }

    Date(int day, int month, int year) {
        this->day = day;
        this->month = month;
        this->year = year;

        time_t timer;
        tm* timeInfo = localtime(&timer);

        timeInfo->tm_mday = day;
        timeInfo->tm_mon = month;
        timeInfo->tm_year = year - 1900;

        mktime(timeInfo);

        this->dayOfWeek = timeInfo->tm_wday;
        
        // delete timeObj;
    }

    int day;
    int year;

    // Months since January (0-11)
    int month;
    // Days since Sunday (0-6)
    int dayOfWeek;
};

#endif