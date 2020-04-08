#include "elevator.h"
#include <algorithm>


Elevator::Elevator(Direction d, int c_timebetweenfloors, int c_floor):
	direction(d),
	motion(Motion::Stopped),
	timeBetweenFloors(c_timebetweenfloors),
	floor(c_floor),
	timer(0)
{

}

void Elevator::addPassenger(Passenger newPassenger)
{

	passengers.push_back(newPassenger);
	if(direction == Direction::Up){
		passengers.sort([](const Passenger &a, const Passenger &b){
							return a.getEndFloor() < b.getEndFloor();
						});
	} else{
		passengers.sort([](const Passenger &a, const Passenger &b){
							return a.getEndFloor() > b.getEndFloor();
						});
	}
}

Passenger Elevator::unboardPassenger()
{
	Passenger temp = passengers.front();
	passengers.pop_front();
	return temp;

}

