#include "TimeHa.h"

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_VALID_YR = 9999;
const int MIN_VALID_YR = 1800;


tm get_current_time()
{
   time_t now = time(0);
   tm *current_time = localtime(&now);
   current_time->tm_mon+=1;
   current_time->tm_year+=1900;

   return *current_time;
}

string get_current_date_string()
{
    string day;
    string month;
    string year;
    stringstream date;

    date << get_current_time().tm_mday << ":" << get_current_time().tm_mon << ":" << get_current_time().tm_year;

    return date.str();
}

bool isLeap(int year)
{
// Return true if year
// is a multiple pf 4 and
// not multiple of 100.
// OR year is multiple of 400.
return (((year % 4 == 0) &&
         (year % 100 != 0)) ||
         (year % 400 == 0));
}

bool isValidDate(string date)
{
    int d, m, y;
    int position;

    position = date.find(":");
    d = atoi(date.substr(0,position).c_str());
    date = date.substr(position+1);

    position = date.find(":");
    m = atoi(date.substr(0,position).c_str());
    date = date.substr(position+1);

    position = date.find(":");
    y = atoi(date.substr(0,position).c_str());



    // If year, month and day
    // are not in given range
    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
    return false;
    if (m < 1 || m > 12)
    return false;
    if (d < 1 || d > 31)
    return false;

    // Handle February month
    // with leap year
    if (m == 2)
    {
        if (isLeap(y))
        return (d <= 29);
        else
        return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}

bool isFirstDateAfter(string first_date, string second_date)
{
    int d1, d2, m1, m2, y1, y2;
    int position;

    //first date
    position = first_date.find(":");
    d1 = atoi(first_date.substr(0,position).c_str());
    first_date = first_date.substr(position+1);

    position = first_date.find(":");
    m1 = atoi(first_date.substr(0,position).c_str());
    first_date = first_date.substr(position+1);

    position = first_date.find(":");
    y1 = atoi(first_date.substr(0,position).c_str());

    //second date
    position = second_date.find(":");
    d2 = atoi(second_date.substr(0,position).c_str());
    second_date = second_date.substr(position+1);

    position = second_date.find(":");
    m2 = atoi(second_date.substr(0,position).c_str());
    second_date = second_date.substr(position+1);

    position = second_date.find(":");
    y2 = atoi(second_date.substr(0,position).c_str());

    if(y1>y2)
    {
        return true;
    }
    else if(y1 == y2 && m1>m2)
    {
        return true;
    }
    else if(y1 == y2 && m1 == m2 && d1>d2)
    {
        return true;
    }
    else
    {
        return false;
    }

}

time_t date_to_sec(string date)
{
    time_t seconds;
    tm test_time = {0};
    int d, m, y;
    int position;

    position = date.find(":");
    d = atoi(date.substr(0,position).c_str());
    date = date.substr(position+1);

    position = date.find(":");
    m = atoi(date.substr(0,position).c_str());
    date = date.substr(position+1);

    position = date.find(":");
    y = atoi(date.substr(0,position).c_str());


    //test_time.tm_hour = 0;
    //test_time.tm_isdst = 0;
    test_time.tm_mday = d;
    //test_time.tm_min = 0;
    test_time.tm_mon = m-1;
    //test_time.tm_sec = 0;
    test_time.tm_year = y-1900;

    seconds = mktime(&test_time);

    //cout << seconds;
    return seconds;
}
