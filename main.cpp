#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Room.h"
#include "Reservation.h"

using namespace std;

void print_mm();
void list_all_rooms();

vector<Room> Rooms;

int main()
{
    int c;
    char ch;
    string line;
    int position;

    int reservation_id;
    int room_id;
    int no_beds;
    string date;
    string name;

    bool vo = false;
    bool done = false;



    fstream database;

    database.open("layout.txt");


    if(database.is_open())
    {
        while(database.good())
        {
            database >> line;
            Rooms.push_back(Room(line));
        }

    }
    else
    {
        printf("Error while opening the file 'layout.txt'.\n" );
    }

    database.close();


    while(done == false)
    {
        print_mm();

        cin >> c;

        switch(c)
        {
        //Check availability
        case 1:
            system("cls");
            cout << "1. Room type\n";
            cout << "2. Enter check-in date\n";
            cout << "3. Enter check--out date\n";
            cout << "4. Check\n";


            vo = false;
            while(vo == false)
            {
                cin >> c;

                switch(c)
                {
                case 1:
                    vo = true;
                    cout << "1. One bed\n";
                    cout << "2. Two beds\n";
                    cin >> c;
                    //something
                    break;
                case 2:
                    vo = true;
                    cout << "Please enter the check-in date: ";
                    cin >> date;
                    break;
                case 3:
                    vo = true;
                    cout << "Please enter the check-out date: ";
                    cin >> date;
                    break;
                case 4:
                    vo = true;
                    //something
                    break;
                default:
                    cout << "Please choose one of the options" << endl;
                }

            }
            system("cls");
            break;
        //Check in
        case 2:
            for (int i = 0; i < Rooms.size(); i++)
            {
                cout << Rooms[i].get_id();
            }
            cout << "---Press any key to continue!---" << endl;
            cin.get(ch);
            cin.get(ch);
            break;
        //Check out
        case 3:

            break;
        //Reservations
        case 4:
            system("cls");
            cout << "1. List all\n";
            cout << "2. List by period\n";
            cout << "3. List by name\n";
            cout << "4. Edit reservation\n";
            cout << "5. Delete reservation\n";

            vo = false;
            while(vo == false)
            {
                cin >> c;

                switch(c)
                {
                case 1:
                    vo = true;
                    for (int i = 0; i < Rooms.size(); i++)
                    {
                        //cout << Rooms[i].get_id();
                        Rooms[i].list_all_reservations();
                    }
                    cout << "---Press any key to continue!---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //something
                    break;
                case 2:
                    vo = true;
                    cout << "Enter the start period(dd-mm-yyyy)" << endl;
                    cin >> date;
                    //do something
                    cout << "Enter the end period(dd-mm-yyyy)" << endl;
                    cin >> date;
                    break;
                case 3:
                    vo = true;
                    cout << "Enter the name" << endl;
                    cin >> name;
                    //do something
                    break;
                case 4:
                    vo = true;
                    cout << "\nEnter the reservation id: ";
                    cin >> reservation_id;
                    //something
                    break;
                case 5:
                    vo = true;
                    cout << "\nEnter the reservation id: ";
                    cin >> reservation_id;
                    //something
                    break;
                default:
                    cout << "Please choose one of the options" << endl;
                }
            }
            system("cls");
            break;

        //List rooms
        case 5:
            system("cls");
            cout << "1. List all\n";
            cout << "2. List reserved\n";
            cout << "3. List free\n";

            vo = false;
            while(vo == false)
            {
                cin >> c;

                switch(c)
                {
                case 1:
                    vo = true;
                    list_all_rooms();
                    cout << "---Press any key to continue!---" << endl;
                    cin.get(ch);
                    cin.get(ch);
                    //do something
                    break;
                case 2:
                    vo = true;
                    //do something
                    break;
                case 3:
                    vo = true;
                    //do something
                    break;
                default:
                    cout << "Please choose one of the options" << endl;
                }
            }
            break;
        case 6:
            done = true;
            break;
        }
    }

}

void list_all_rooms()
{
    system("cls");
    cout << "Listing all rooms: " << endl << endl;

    //cout << Rooms[0].get_id() << "  ";
    //cout << Rooms[0].get_beds() << endl;

    //vector<int>::iterator it = Rooms.begin();

    for (int i = 0; i < Rooms.size(); i++)
    {
        cout << "Room id: " << Rooms[i].get_id() << "  ";
        cout << "\tNumber of beds: " << Rooms[i].get_beds() << endl;
    }
    cout << endl;
}

void print_mm()
{
    system("cls");
    cout << "\tMain menu\n\n";
    cout << "Please choose an option\n";

    cout << "\n1. Check Availability\n";
    cout << "2. Check-in\n";
    cout << "3. Check-out\n";
    cout << "4. Reservations\n";
    cout << "5. List rooms\n";
    cout << "6. Quit\n";
}
