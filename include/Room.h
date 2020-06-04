#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

using namespace std;

class Room
{
    public:
        Room(string room_parameters);
        ~Room();
        bool available(string check_in, string check_out);
        void list_all_reservations();
        int get_id();
        int get_beds();

    protected:

    private:
        int room_id;
        int no_beds;
        //vector<Reservation> Reservations;
};

#endif // ROOM_H
