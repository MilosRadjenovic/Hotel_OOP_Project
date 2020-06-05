#ifndef DOUBLEBEDROOM_H
#define DOUBLEBEDROOM_H

#include <Room.h>


class DoubleBedRoom : public Room
{
    public:
        DoubleBedRoom(string room_parameters)
        : Room(room_parameters)
        {

        }
        int get_beds();

    protected:

    private:
        int no_beds = 2;
};

#endif // DOUBLEBEDROOM_H
