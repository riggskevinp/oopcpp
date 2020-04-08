#include "floor.h"

Floor::Floor()
{

}

void Floor::addPassenger(Passenger p)
{
	if(p.getDirection() == Direction::Up){
		this->UpPassengers.push(p);
	} else{
		this->DownPassengers.push(p);
	}
}
