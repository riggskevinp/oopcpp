#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <list>

#include "direction.h"
#include "passenger.h"

enum class Motion{Moving,Stopping,Stopped};

class Elevator
{
public:
	Elevator(Direction d = Direction::Up, int c_timebetweenfloors = 10, int c_floor = 0);
	void addPassenger(Passenger newPassenger);
	Passenger unboardPassenger();

private:
	Direction direction;
	Motion motion;
	int timeBetweenFloors;
	//next floor a passenger could get off or on
	//could be the floor moving to or stopped at.
	int floor;
	int timer;
	std::list<Passenger> passengers;

};

#endif // ELEVATOR_H
