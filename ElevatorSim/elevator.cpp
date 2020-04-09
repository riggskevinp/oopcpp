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

bool Elevator::addPassenger(Floor *f)
{
	if(passengers.size() >= 8){
		return false;
	}
	if(passengers.size() <= 0){
		if(!f->UpPassengers.empty()){
			addPassenger(f->UpPassengers.front());
			f->UpPassengers.pop();
			direction = Direction::Up;
			return true;
		}
		if(!f->DownPassengers.empty()){
			addPassenger(f->DownPassengers.front());
			f->DownPassengers.pop();
			direction = Direction::Down;
			return true;
		}
	}
	if(direction == Direction::Up){
		if(!f->UpPassengers.empty()){
			addPassenger(f->UpPassengers.front());
			f->UpPassengers.pop();
			return true;
		}
		return false;
	}else{
		if(!f->DownPassengers.empty()){
			addPassenger(f->DownPassengers.front());
			f->DownPassengers.pop();
			return true;
		}
		return false;
	}
}

Passenger Elevator::unboardPassenger()
{
	if(passengers.front().getEndFloor() == floor){
		Passenger temp = passengers.front();
		passengers.pop_front();
		return temp;
	}

}

bool Elevator::tryUnloadPassenger()
{
	for(auto p : passengers){
		if(p.getEndFloor() == floor){
			return true;
		}
	}
	return false;
}

void Elevator::startMoving(Direction d)
{
	motion = Motion::Moving;
	direction = d;
	timer += timeBetweenFloors;
}

void Elevator::passFloor()
{
	timer += timeBetweenFloors;
	if(direction == Direction::Up){
		if(floor <= 99){
			floor++;
		} else{
			floor--;
			direction = Direction::Down;
		}
	}else{
		if(floor >= 1){
			floor--;
		} else{
			floor++;
			direction = Direction::Up;
		}
	}
}

bool Elevator::passengerNeedsStop()
{
	for(auto p : passengers){
		if(p.getEndFloor() == floor){
			return true;
		}
	}

	return false;

}

void Elevator::stopping()
{
	timer += timeToStop;
	motion = Motion::Stopping;
}

