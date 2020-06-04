#include "Room.h"

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Reservation.h"

using namespace std;

vector<Reservation> Reservations;

Room::Room(string room_parameters)
{
    int position;
    string line;

    position = room_parameters.find("|");
    //room_id = (room_parameters.substr(0,position));
    room_id = atoi(room_parameters.substr(0,position).c_str());

    room_parameters = room_parameters.substr(position+1);

    position = room_parameters.find("|");
    //no_beds = (room_parameters.substr(0,position));
    no_beds = atoi(room_parameters.substr(0,position).c_str());

    //cout << room_id << " ";
    //cout << no_beds << endl;




    string temp;

    fstream database;

    database.open("reservations.txt");


    if(database.is_open())
    {
        while(database.good())
        {
            database >> line;
            //cout << "1. " << line << endl;
            position = line.find("|");
            temp = line.substr(position+1);
            //cout << "2. " << line << endl;
            position = temp.find("|");

            temp = temp.substr(0,position);

            //cout << "3. " << temp << endl;

            if(atoi(temp.c_str()) == room_id )
            {
                Reservations.push_back(Reservation(line));
            }



        }

    }
    else
    {
        printf("Error while opening the file 'reservations.txt'.\n" );
    }

    database.close();


    //ctor
}

Room::~Room()
{
    //dtor
}

int Room::get_id()
{
    return room_id;
}

int Room::get_beds()
{
    return no_beds;
}

void Room::list_all_reservations()
{
    system("cls");
    cout << "Listing all reservations: " << endl << endl;
    cout << "\tRoom id: " << this->get_id() << endl;

    for (int i = 0; i < Reservations.size(); i++)
    {
        cout << "Reservation id: " << Reservations[i].get_id() << "  ";
        cout << "\tIn room: " << this->get_id();
        cout << "\tName: " << Reservations[i].get_first_name() << " " << Reservations[i].get_last_name();
        cout << "\tFrom: " << Reservations[i].get_check_in() << " To: " << Reservations[i].get_check_out() << endl;
        //cout << "\tFrom: " << Reservations[i].get_check_in() << "  To: " << Reservation[i].get_check_out() << endl;
    }
    cout << endl;
}
