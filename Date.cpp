#include "Date.h"
using namespace std;

Date::Date(int day, int month, int year)
{
    this->year = year;
    this->month = month;
    this->day = day;
    hours = 0;
    minutes = 0;
}

Date::Date()
{
    time_t now = time(0);

    tm* ltm = localtime(&now);
    year = PRE_HISTORIC + ltm->tm_year;
    month = 1 + ltm->tm_mon;
    day = ltm->tm_mday;
    hours = ltm->tm_hour;
    minutes = ltm->tm_min;
}

Date::Date(const Date& other)
{
    day = other.day;
    month = other.month;
    year = other.year;
    hours = other.hours;
    minutes = other.minutes;
}

Date::Date(ifstream& in)
{
    in >> *this;
}

void Date::dayShow() const
{
    if (day < TWO_DIGITS)
        cout << "0";
    cout << day << "/";

    if (month < TWO_DIGITS)
        cout << "0";
    cout << month << "/";
    cout << year;
}

void Date::timeShow() const
{
    if (hours < TWO_DIGITS)
        cout << "0";
    cout << hours << ":";

    if (minutes < TWO_DIGITS)
        cout << "0";
    cout << minutes << endl;
}

const int Date::getYear()	const
{
    return year;
}

const int Date::getMonth() const
{
    return month;
}

const int Date::getDay()	const
{
    return day;
}

const int Date::getHour()	const
{
    return hours;
}

const int Date::getMinute() const
{
    return minutes;
}

// operators:

void Date::operator=(const Date& other)
{
    day = other.day;
    month = other.month;
    year = other.year;
    hours = other.hours;
    minutes = other.minutes;
}

ostream& operator<<(ostream& os, const Date& d)
{
    // writes to file: Date's day, month, year, hours, minutes
    os << d.day << "/" << d.month << "/" << d.year << " " << d.hours << ":" << d.minutes;
    return os;
}

istream& operator>>(istream& in, Date& d)
{
    char delimeter;
    // Reads from file: Date's day, month, year, hours, minutes
    in >> d.day >> delimeter >> d.month >> delimeter >> d.year >> d.hours >> delimeter >> d.minutes;

    return in;
}