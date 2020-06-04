#ifndef RESERVATION_H
#define RESERVATION_H

#include <Room.h>
#include <string>


class Reservation
{
    public:
        Reservation(string reservation_data);
        ~Reservation();
        int get_id();
        string get_first_name();
        string get_last_name();
        string get_check_in();
        string get_check_out();

    protected:

    private:
        int reservation_id;
        string first_name;
        string last_name;
        string check_in;
        string check_out;
};

#endif // RESERVATION_H
