#ifndef TIMEHA_H
#define TIMEHA_H

#include <iostream>
#include <ctime>
#include <string>

using namespace std;

tm get_current_time();
string get_current_date_string();
bool isValidDate(string date);
bool isFirstDateAfter(string first_date, string second_date);

time_t date_to_sec(string date);

#endif // TIMEHA_H
