#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#include "Room.h"
#include "Reservation.h"
#include "TimeHa.h"
#include "SingleBedRoom.h"
#include "DoubleBedRoom.h"

using namespace std;

void print_mm();
void list_all_rooms();
string int2s(int a);

vector<Room> Rooms;
vector<SingleBedRoom> SingleBedRooms;
vector<DoubleBedRoom> DoubleBedRooms;

int main()
{
    char c;
    char ch;
    string line;
    string temp_line;
    int position;

    int reservation_id;
    int room_id;
    int no_beds;
    char room_type = '1';
    string check_in = "2:2:2022";//"dd:mm:yyyy";
    string check_out = "2:3:2022";//"dd:mm:yyyy";
    string date;
    string f_name;
    string l_name;
    string room_number;

    bool vo = false;
    bool done = false;
    bool found;



    fstream database;

    database.open("layout.txt");


    if(database.is_open())
    {
        while(database.good())
        {
            database >> line;

            position = line.find("|");
            temp_line = line.substr(position+1);
            position = temp_line.find("|");
            no_beds = atoi(temp_line.substr(0,position).c_str());

            if(no_beds == 1)
            {
                SingleBedRooms.push_back(SingleBedRoom(line));
            }
            else if(no_beds == 2)
            {
                DoubleBedRooms.push_back(DoubleBedRoom(line));
            }
            //Rooms.push_back(Room(line));
        }

    }
    else
    {
        printf("Error while opening the file 'layout.txt'.\n" );
    }

    database.close();

    #define MENU_ACTIVE

    #ifdef MENU_ACTIVE
    while(done == false)
    {
        print_mm();

        cin >> c;

        switch(c)
        {
        //Check availability
        case '1':
            /*system("cls");

            cout << "1. Room type: " << room_type << endl;
            cout << "2. Enter check-in date\n";
            cout << "3. Enter check--out date\n";
            cout << "4. Check\n";
            cout << "\n5. Go back\n";*/


            vo = false;
            while(vo == false)
            {
                system("cls");
                cout << "1. Room type: " << room_type << " beds" << endl;
                cout << "2. Enter check-in date: " << check_in << endl;
                cout << "3. Enter check--out date: " << check_out << endl;
                cout << "4. Check\n";
                cout << "\n5. Go back\n";

                cin >> c;

                switch(c)
                {
                case '1':
                    //vo = true;
                    cout << "1. One bed\n";
                    cout << "2. Two beds\n";
                    cin >> c;
                    if(c != '1' && c != '2')
                    {
                        cout << "Please choose option 1 or 2\n";
                    }
                    else
                    {
                        room_type = c;
                    }
                    //something
                    break;
                case '2':
                    //vo = true;
                    cout << "Please enter the check-in date (dd:mm:yyyy): ";
                    cin >> date;
                    if(isValidDate(date) == true)
                    {
                        check_in = date;
                    }
                    else
                    {
                        cout << "Invalid date" << endl;
                        cin.get(ch);
                        cin.get(ch);
                    }
                    break;
                case '3':
                    //vo = true;
                    cout << "Please enter the check-out date (dd:mm:yyyy): ";
                    cin >> date;
                    if(isValidDate(date) == true)
                    {
                        check_out = date;
                    }
                    else
                    {
                        cout << "Invalid date" << endl;
                        cin.get(ch);
                        cin.get(ch);
                    }
                    break;
                case '4':
                    vo = true;
                    found = false;
                    cout << endl;
                    if(room_type == '1')
                    {
                        for (int i = 0; i < SingleBedRooms.size(); i++)
                        {
                            if(SingleBedRooms[i].available(check_in, check_out) == true)
                            {
                                if(isFirstDateAfter(check_out, check_in))
                                {
                                    cout << "Room: "<< SingleBedRooms[i].get_id() << " is free at that time" << endl;
                                    room_number = int2s(SingleBedRooms[i].get_id());
                                    found = true;
                                }
                                else
                                {
                                    cout << "Check out date cannot be before the check in date!" << endl;
                                }
                            }
                        }
                    }
                    else if(room_type == '2')
                    {
                        for (int i = 0; i < DoubleBedRooms.size(); i++)
                        {
                            if(DoubleBedRooms[i].available(check_in, check_out) == true)
                            {
                                if(isFirstDateAfter(check_out, check_in))
                                {
                                     cout << "Room: "<< DoubleBedRooms[i].get_id() << " is free at that time" << endl;
                                    room_number = int2s(DoubleBedRooms[i].get_id());
                                    found = true;
                                }
                                else
                                {
                                    cout << "Check out date cannot be before the check in date!" << endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        system("cls");
                        cout << "Unexpected error!!" << endl;
                        cout << "---Press any key to terminate---" << endl;
                        cin.get(ch);
                        cin.get(ch);
                        done = true;
                    }
                    if(found == false)
                    {
                        cout << "There are no available rooms at that time" << endl;
                    }

                    cout << "\n---Press any key to continue---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //something
                    break;
                case '5':
                    vo = true;
                    //go back
                    break;
                default:
                    cout << "Please choose one of the options" << endl;
                }

            }
            system("cls");
            break;
        //Check in
        case '2':
            /*for (int i = 0; i < Rooms.size(); i++)
            {
                cout << Rooms[i].get_id();
            }*/

            date_to_sec("2:3:2020");

            cout << "---Press any key to continue!---" << endl;
            cin.get(ch);
            cin.get(ch);
            break;
        //Check out
        case '3':
            cout << get_current_time().tm_mday;
            cout << ":" << get_current_time().tm_mon;
            cout << ":" << get_current_time().tm_year << endl;
            cout << "---Press any key to continue!---" << endl;
            cin.get(ch);
            cin.get(ch);

            break;
        //Reservations
        case '4':
            system("cls");
            cout << "1. List all\n";
            cout << "2. List by period --(not finished)\n";
            cout << "3. List by name\n";
            cout << "4. Make new reservation\n";
            cout << "5. Edit reservation --(not finished)\n";
            cout << "6. Delete reservation\n";
            cout << "\n7. Go back\n";

            vo = false;
            while(vo == false)
            {
                cin >> c;

                switch(c)
                {
                case '1':
                    vo = true;
                    system("cls");
                    cout << "Listing all reservations: " << endl << endl;
                    for (int i = 0; i < SingleBedRooms.size(); i++)
                    {
                        //cout << Rooms[i].get_id();
                        SingleBedRooms[i].list_all_reservations();
                    }
                    for (int i = 0; i < DoubleBedRooms.size(); i++)
                    {
                        //cout << Rooms[i].get_id();
                        DoubleBedRooms[i].list_all_reservations();
                    }
                    cout << "---Press any key to continue!---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //something
                    break;
                case '2':
                    vo = true;
                    cout << "Enter the start period(dd-mm-yyyy)" << endl;
                    cin >> date;
                    //do something
                    cout << "Enter the end period(dd-mm-yyyy)" << endl;
                    cin >> date;
                    break;
                case '3':
                    vo = true;
                    found = false;
                    system("cls");
                    cout << "Enter the first name" << endl;
                    cin >> f_name;
                    cout << "Enter the last name" << endl;
                    cin >> l_name;

                    cout << "Listing all reservations for: " << f_name << " " << l_name << endl << endl;

                    for (int i = 0; i < SingleBedRooms.size(); i++)
                    {
                        found |= SingleBedRooms[i].list_reservations_by_name(f_name, l_name);
                    }
                    for (int i = 0; i < DoubleBedRooms.size(); i++)
                    {
                        found |= DoubleBedRooms[i].list_reservations_by_name(f_name, l_name);
                    }

                    if(found == false)
                    {
                        cout << "There are no active reservations for that name. " << endl;
                    }

                    cout << endl << "---Press any key to continue!---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //do something
                    break;
         //Make reservation
                case '4':
                    vo = false;
                    while(vo == false)
                    {
                        system("cls");
                        cout << "1. Room type: " << room_type << endl;
                        cout << "2. Enter check-in date: " << check_in << endl;
                        cout << "3. Enter check--out date: " << check_out << endl;
                        cout << "4. Room number: " << room_number << endl;
                        cout << "5. First name: " << f_name << endl;
                        cout << "6. Last name: " << l_name << endl;
                        cout << "7. Reserve\n";
                        cout << "\n8. Go back\n";

                        cin >> c;

                        switch(c)
                        {
                        case '1':
                            //vo = true;
                            cout << "1. One bed\n";
                            cout << "2. Two beds\n";
                            cin >> c;
                            if(c != '1' && c != '2')
                            {
                                cout << "Please choose option 1 or 2\n";
                            }
                            else
                            {
                                room_type = c;
                            }
                            //something
                            break;
                        case '2':
                            //vo = true;
                            cout << "Please enter the check-in date (dd:mm:yyyy): ";
                            cin >> date;
                            if(isValidDate(date) == true)
                            {
                                check_in = date;
                            }
                            else
                            {
                                cout << "Invalid date" << endl;
                                cin.get(ch);
                                cin.get(ch);
                            }
                            break;
                        case '3':
                            //vo = true;
                            cout << "Please enter the check-out date (dd:mm:yyyy): ";
                            cin >> date;
                            if(isValidDate(date) == true)
                            {
                                check_out = date;
                            }
                            else
                            {
                                cout << "Invalid date" << endl;
                                cin.get(ch);
                                cin.get(ch);
                            }
                            break;
                        case '4':
                            cout << "Enter the room number: ";
                            cin >> room_number;
                            break;
                        case '5':
                            cout << "Enter your first name: ";
                            cin >> f_name;
                            break;
                        case '6':
                            cout << "Enter your last name: ";
                            cin >> l_name;
                            break;
                        case '7':
                            vo = true;
                            found = false;
                            cout << endl;
                            if(room_type == '1')
                            {
                                for (int i = 0; i < SingleBedRooms.size(); i++)
                                {
                                    if(SingleBedRooms[i].get_id() == atoi(room_number.c_str()))
                                    {
                                        if(isFirstDateAfter(check_out, check_in) == true)
                                        {
                                            found = SingleBedRooms[i].make_reservation(check_in, check_out, room_number, f_name, l_name);
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Check out date cannot be before the check in date!" << endl;
                                        }
                                    }
                                }
                            }
                            else if(room_type == '2')
                            {
                                for (int i = 0; i < DoubleBedRooms.size(); i++)
                                {
                                    if(DoubleBedRooms[i].get_id() == atoi(room_number.c_str()))
                                    {
                                        if(isFirstDateAfter(check_out, check_in) == true)
                                        {
                                            found = DoubleBedRooms[i].make_reservation(check_in, check_out, room_number, f_name, l_name);
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Check out date cannot be before the check in date!" << endl;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                system("cls");
                                cout << "Unexpected error!!" << endl;
                                cout << "---Press any key to terminate---" << endl;
                                cin.get(ch);
                                cin.get(ch);
                                done = true;
                            }
                            if(found == false)
                            {
                                cout << "There are no available rooms with those parameters" << endl;
                            }
                            else
                            {
                                cout << "Reservation was successful" << endl;
                            }

                            cout << "\n---Press any key to continue---" << endl;
                            cin.get(ch);
                            cin.get(ch);
                            //something
                            break;
                        case '8':
                            vo = true;
                            //go back
                            break;
                        default:
                            cout << "Please choose one of the options" << endl;
                        }

                    }
                    system("cls");

                    break;
            //Edit reservation
                case '5':
                    vo = true;
                    cout << "\nEnter the reservation id: ";
                    cin >> reservation_id;
                    found = false;
                    for (int i = 0; i < SingleBedRooms.size(); i++)
                    {
                        if(SingleBedRooms[i].edit_reservation(reservation_id) == true)
                        {
                            found = true;
                            break;
                        }
                    }
                    for (int i = 0; i < DoubleBedRooms.size() && found == false; i++)
                    {
                        if(DoubleBedRooms[i].edit_reservation(reservation_id) == true)
                        {
                            found = true;
                            break;
                        }
                    }
                    if(found == true)
                    {
                        cout << "Reservation changed successfully" << endl;
                    }
                    else
                    {
                        cout << "Reservation with that id couldn't be found" << endl;
                    }
                    cout << "\n---Press any key to continue---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //something
                    break;
        //Delete reservation
                case '6':
                    vo = true;
                    cout << "\nEnter the reservation id: ";
                    cin >> reservation_id;
                    found = false;
                    for (int i = 0; i < SingleBedRooms.size(); i++)
                    {
                        if(SingleBedRooms[i].delete_reservation(reservation_id) == true)
                        {
                            found = true;
                            break;
                        }
                    }
                    for (int i = 0; i < DoubleBedRooms.size() && found == false; i++)
                    {
                        if(DoubleBedRooms[i].delete_reservation(reservation_id) == true)
                        {
                            found = true;
                            break;
                        }
                    }
                    if(found == true)
                    {
                        cout << "Reservation deleted successfully" << endl;
                    }
                    else
                    {
                        cout << "Reservation with that id couldn't be found" << endl;
                    }
                    cout << "\n---Press any key to continue---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //something
                    break;
                case '7':
                    vo = true;
                    //go back
                    break;
                default:
                    cout << "Please choose one of the options" << endl;
                    //c = 1;
                }
            }
            system("cls");
            break;

        //List rooms
        case '5':
            system("cls");
            cout << "1. List all\n";
            cout << "2. List reserved --(not finished)\n";
            cout << "3. List free --(not finished)\n";
            cout << "\n4. Go back\n";

            vo = false;
            while(vo == false)
            {
                cin >> c;

                switch(c)
                {
                case '1':
                    vo = true;
                    list_all_rooms();
                    cout << "---Press any key to continue!---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //do something
                    break;
                case '2':
                    vo = true;
                    //do something
                    break;
                case '3':
                    vo = true;
                    //do something
                    break;
                case '4':
                    vo = true;
                    //go back
                    break;
                default:
                    cout << "Please choose one of the options" << endl;
                }
            }
            break;
        case '6':
            done = true;
            break;
        }
    }
    #endif // MENU_ACTIVE
}

void list_all_rooms()
{
    system("cls");
    cout << "Listing all rooms: " << endl << endl;

    //cout << Rooms[0].get_id() << "  ";
    //cout << Rooms[0].get_beds() << endl;

    //vector<int>::iterator it = Rooms.begin();

    for (int i = 0; i < SingleBedRooms.size(); i++)
    {
        cout << "Room id: " << SingleBedRooms[i].get_id() << "  ";
        cout << "\tNumber of beds: " << SingleBedRooms[i].get_beds() << endl;
    }

    for (int i = 0; i < DoubleBedRooms.size(); i++)
    {
        cout << "Room id: " << DoubleBedRooms[i].get_id() << "  ";
        cout << "\tNumber of beds: " << DoubleBedRooms[i].get_beds() << endl;
    }

    cout << endl;
}

void print_mm()
{
    system("cls");
    cout << "\tMain menu\n\n";
    cout << "Please choose an option\n";

    cout << "\n1. Check Availability\n";
    cout << "2. Check-in --(not finished)\n";
    cout << "3. Check-out --(not finished)\n";
    cout << "4. Reservations\n";
    cout << "5. List rooms\n";
    cout << "6. Quit\n";
}

string int2s(int a)
{
    string ss="";   //create empty string
    while(a)
    {
        int x=a%10;
        a/=10;
        char i='0';
        i=i+x;
        ss=i+ss;      //append new character at the front of the string!
    }
    return ss;
}
