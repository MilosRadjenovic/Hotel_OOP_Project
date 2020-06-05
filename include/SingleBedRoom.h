#ifndef SINGLEBEDROOM_H
#define SINGLEBEDROOM_H

#include <Room.h>


class SingleBedRoom : public Room
{
    public:
        SingleBedRoom(string room_parameters)
        : Room(room_parameters)
        {

        }
        int get_beds();

    protected:

    private:
        int no_beds = 1;
};

#endif // SINGLEBEDROOM_H
