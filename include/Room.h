#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

using namespace std;
class Reservation;
class Room
{
    public:
        Room(string room_parameters);
        ~Room();
        bool available(string check_in, string check_out);
        bool make_reservation(string check_in, string check_out, string room_number, string f_name, string l_name);
        bool delete_reservation(int reservation_id);
        bool edit_reservation(int reservation_id);
        void list_all_reservations();
        bool list_reservations_by_name(string f_name, string l_name);
        int get_id();
        //int get_beds();
        static int new_reservation_id;

    protected:

    private:
        int room_id; //same as room number
        //int no_beds;
        vector<Reservation> Reservations;
};

#endif // ROOM_H
