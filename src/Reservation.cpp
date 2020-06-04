#include "Reservation.h"

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


Reservation::Reservation(string reservation_data)
{
    int position;

    position = reservation_data.find("|");
    reservation_id = atoi(reservation_data.substr(0,position).c_str());

    reservation_data = reservation_data.substr(position+1);
    position = reservation_data.find("|");
    reservation_data = reservation_data.substr(position+1);
    position = reservation_data.find("|");
    first_name = reservation_data.substr(0, position);

    reservation_data = reservation_data.substr(position+1);
    position = reservation_data.find("|");
    last_name = reservation_data.substr(0, position);

    reservation_data = reservation_data.substr(position+1);
    position = reservation_data.find("|");
    check_in = reservation_data.substr(0, position);

    reservation_data = reservation_data.substr(position+1);
    position = reservation_data.find("|");
    check_out = reservation_data.substr(0, position);


    //ctor
}

Reservation::~Reservation()
{
    //dtor
}

int Reservation::get_id()
{
    return reservation_id;
}

string Reservation::get_first_name()
{
    return first_name;
}

string Reservation::get_last_name()
{
    return last_name;
}

string Reservation::get_check_in()
{
    return check_in;
}

string Reservation::get_check_out()
{
    return check_out;
}
