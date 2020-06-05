#include "Room.h"

#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Reservation.h"
#include "TimeHa.h"

using namespace std;

int Room::new_reservation_id;
int countLine(char* sourcefile);
void removeLine(char* sourcefile,int line);
//vector<Reservation> Reservations;

Room::Room(string room_parameters)
{
    int position;
    string line;

    position = room_parameters.find("|");
    //room_id = (room_parameters.substr(0,position));
    room_id = atoi(room_parameters.substr(0,position).c_str());

    room_parameters = room_parameters.substr(position+1);

    position = room_parameters.find("|");

    //no_beds = atoi(room_parameters.substr(0,position).c_str());

    //cout << room_id << " ";
    //cout << no_beds << endl;




    string temp;
    string temp_room_id;
    string check_in, check_out;
    string current_id;

    fstream database;

    database.open("reservations.txt");

    if(database.is_open())
    {
        while(database.good())
        {
            database >> line;
            //cout << "1. " << line << endl;
            position = line.find("|");
            current_id = line.substr(0, position);
            temp = line.substr(position+1);
            //cout << "2. " << temp << endl;
            position = temp.find("|");

            temp_room_id = temp.substr(0,position);

            //getting to the dates
            temp = temp.substr(position+1);
            //cout << "4. " << temp << endl;
            position = temp.find("|");
            temp = temp.substr(position+1);
            //cout << "5. " << temp << endl;
            position = temp.find("|");
            temp = temp.substr(position+1);
            //cout << "6. " << temp << endl;

            //Dates---
            position = temp.find("|");
            check_in = temp.substr(0,position);
            temp = temp.substr(position+1);

            position = temp.find("|");
            check_out = temp.substr(0,position);

            //temp = get_current_time().tm_mday+":"+get_current_time().tm_mon+":"+get_current_time().tm_year;

            temp = get_current_date_string();


            //cout << "f. " << temp << endl;
            //cout << "check in: " << check_in << endl;
            //cout << "check out: " << check_out << endl;


            if(atoi(temp_room_id.c_str()) == room_id && isFirstDateAfter(check_out, temp) == true)
            {
                Reservations.push_back(Reservation(line));
            }
        }

        new_reservation_id = atoi(current_id.c_str())+1;
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

/*int Room::get_beds()
{
    return no_beds;
}*/

bool Room::available(string check_in, string check_out)
{
    bool result = true;
    int required_check_in = date_to_sec(check_in);
    int required_check_out = date_to_sec(check_out);

    for (int i = 0; i < Reservations.size(); i++)
    {
        /*cout << "req check in: " << required_check_in << endl;
        cout << "req check out: " << required_check_out << endl;
        cout << "existing check in: " << date_to_sec(Reservations[i].get_check_in()) << endl;
        cout << "existing check out: " << date_to_sec(Reservations[i].get_check_out()) << endl;*/
        //if(!(required_check_in < date_to_sec(Reservations[i].get_check_in()) && required_check_out < date_to_sec(Reservations[i].get_check_in())))
        if(required_check_in >= date_to_sec(Reservations[i].get_check_in()) && required_check_in <= date_to_sec(Reservations[i].get_check_out()))
        {
            result = false;
            break;
        }
        //else if(!(required_check_in > date_to_sec(Reservations[i].get_check_out()) && required_check_out > date_to_sec(Reservations[i].get_check_out())))
        else if(required_check_out >= date_to_sec(Reservations[i].get_check_in()) && required_check_out <= date_to_sec(Reservations[i].get_check_out()))
        {
            result = false;
            break;
        }
    }
    //cout << "result: " << result << endl;
    //cout << "room id: " << room_id << endl;
    //cout << "---Press any key to terminate---" << endl;
    //cin.get();
    //cin.get();
    return result;
}


bool Room::make_reservation(string check_in, string check_out, string room_number, string f_name, string l_name)
{
    stringstream reservation_parameters;
    fstream database;

    reservation_parameters << new_reservation_id << "|" << room_number << "|" << f_name << "|" << l_name << "|" << check_in << "|" << check_out << "|";

    if(available(check_in, check_out) == true)
    {
        //cout << "parameters: " << reservation_parameters.str() << endl;

        database.open("reservations.txt", fstream::app);

        if(database.is_open())
        {
            while(database.good())
            {
                database << endl << reservation_parameters.str();
                break;
            }
        }
        database.close();

        Reservations.push_back(Reservation(reservation_parameters.str()));
        new_reservation_id++;

        return true;
    }
    else
    {
        return false;
    }
}


bool Room::delete_reservation(int reservation_id)
{
    fstream database;
    string line;
    string current_id;
    int position;
    int j = 0;
    bool found = false;

    for (int i = 0; i < Reservations.size(); i++)
    {
        if(Reservations[i].get_id() == reservation_id)
        {
            Reservations[i].~Reservation();
            Reservations.erase(Reservations.begin()+i);

            database.open("reservations.txt");

            if(database.is_open())
            {
                while(!database.eof())
                {
                    database >> line;
                    j++;

                    position = line.find("|");
                    current_id = line.substr(0, position);
                    if(atoi(current_id.c_str()) == reservation_id)
                    {
                        found = true;
                        //database << endl;
                        break;
                    }
                }
            }
            database.close();
            if(found == true)
            {
                 removeLine("reservations.txt", j);
                 return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

bool Room::edit_reservation(int reservation_id)
{
    return true;
}


void Room::list_all_reservations()
{
    for (int i = 0; i < Reservations.size(); i++)
    {
        cout << "Reservation id: " << Reservations[i].get_id() << "  ";
        cout << "\tIn room: " << room_id;
        cout << "\tName: " << Reservations[i].get_first_name() << " " << Reservations[i].get_last_name();
        cout << "\tFrom: " << Reservations[i].get_check_in() << " To: " << Reservations[i].get_check_out() << endl;;
    }
    cout << endl;
}

bool Room::list_reservations_by_name(string f_name, string l_name)
{
    bool found;;
    found = false;

    for (int i = 0; i < Reservations.size(); i++)
    {
        if(Reservations[i].get_first_name() == f_name && Reservations[i].get_last_name() == l_name)
        {
            cout << "Reservation id: " << Reservations[i].get_id() << "  ";
            cout << "\tIn room: " << room_id;
            cout << "\tFrom: " << Reservations[i].get_check_in() << " To: " << Reservations[i].get_check_out() << endl;
            found = true;
        }
        //cout << "i: " << i << endl;
    }
    /*if(found == false && current_room == last_room)
    {
        cout << "There are no active reservations for that name. " << endl;
    }*/
    //cout << "testing purposes" << endl;
    //cout << "current room: " << current_room << endl;
    //cout << "last room: " << last_room << endl;
    //cout << endl;
    return found;
}

void removeLine(char* sourcefile,int line)
{
    ifstream infile;
    char tempPath[100]="tempfile.txt";
    infile.open(sourcefile,ios::in);
    if(infile)
    {
        int numLine=countLine(sourcefile);
        if(numLine<line)
        {
            cout<<"\nNo line to delete\n.";
            return;
        }

        ofstream outfile;
        outfile.open(tempPath,ios::out);
        char data[100];
        int i=0;
        while(infile.getline(data,100))
        {
            i++;
            if(i==line) continue;
            outfile<<data<<"\n";
        }
        outfile.close();
    }

    infile.close();
    remove(sourcefile);
    rename(tempPath,sourcefile);

}

int countLine(char* sourcefile)
{
    ifstream infile;
    infile.open(sourcefile,ios::in);
    char data[100];
    int line=0;

    while(infile.getline(data,100)) line++;
    return line;
}

