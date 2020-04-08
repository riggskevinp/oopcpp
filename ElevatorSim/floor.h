#ifndef FLOOR_H
#define FLOOR_H

#include <queue>

#include "passenger.h"

class Floor
{
public:
	Floor();
	void addPassenger(Passenger p);
	std::queue<Passenger> UpPassengers;
	std::queue<Passenger> DownPassengers;

private:


};

#endif // FLOOR_H
