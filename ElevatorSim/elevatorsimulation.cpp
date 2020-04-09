#include "elevatorsimulation.h"

ElevatorSim::ElevatorSim():
	floors(101,Floor())
{
	using namespace elevatorutils;
	elevatorutils::readCSV("Mod10_Assignment_Elevators.csv", passengerQueue);
}

int ElevatorSim::run()
{
	sumOfTravelTimes = 0;
	passengersAtDestination = 0;
	int numberOfPassengers = passengerQueue.size();

	for(timer = 0; timer <= 40000; timer++){
		bool isEmpty = true;
		isEmpty = passengerQueue.empty();
			while(!isEmpty && passengerQueue.front().getStartTime() <= timer){
				floors[passengerQueue.front().getStartFloor()].addPassenger(passengerQueue.front());
				passengerQueue.pop();
				isEmpty = passengerQueue.empty();
			}

		for(auto &e : elevators){
			operate(*e);
		}

	}
	std::cout << sumOfTravelTimes << " " << numberOfPassengers << std::endl;
	return sumOfTravelTimes / numberOfPassengers;
}

bool ElevatorSim::floorsEmpty()
{
	for(auto f : floors){
		if(!f.UpPassengers.empty() || !f.DownPassengers.empty()){
			return false;
		}
	}
	return true;
}

bool ElevatorSim::floorEmpty(int floor)
{
	return floors.at(floor).UpPassengers.empty() && floors.at(floor).DownPassengers.empty();
}

Direction ElevatorSim::getOccupiedFloorDirection(int floorNumber)
{
	std::vector<Floor>::iterator itr;
	for(itr = floors.begin(); itr < floors.end(); itr++){
		if(!itr->UpPassengers.empty() || !itr->DownPassengers.empty()){
			int index = std::distance(floors.begin(),itr);
			if(floorNumber > index){
				return Direction::Down;
			}else{
				return Direction::Up;
			}
		}
	}
}

Direction ElevatorSim::getClosestOccupiedFloorDirection(int floorNumber)
{
	int distanceDown = 101;
	int distanceUp = distanceDown;

	std::vector<Floor>::reverse_iterator ritr;
	for(ritr = floors.rbegin() + floorNumber; ritr < floors.rend(); ritr++){
		if(!ritr->UpPassengers.empty() || !ritr->DownPassengers.empty()){
			int distanceDown = std::distance(floors.rbegin(),ritr);
			/*
			if(floorNumber > index){
				return Direction::Down;
			}else{
				return Direction::Up;
			}*/
		}
	}

	std::vector<Floor>::iterator itr;
	for(itr = floors.begin() + floorNumber; itr < floors.end(); itr++){
		if(!itr->UpPassengers.empty() || !itr->DownPassengers.empty()){
			int distanceUp = std::distance(floors.begin(),itr);
			/*
			if(floorNumber > index){
				return Direction::Down;
			}else{
				return Direction::Up;
			}*/
		}
	}
	if(distanceUp > distanceDown){
		return Direction::Up;
	}else{
		return Direction::Down;
	}
}

bool ElevatorSim::floorHasPassengersInSameDirection(int f, Direction d)
{
	if(d == Direction::Up){
		return !floors.at(f).UpPassengers.empty();
	}else{
		return !floors.at(f).DownPassengers.empty();
	}
}

void ElevatorSim::operate(Elevator &e)
{
	if(e.isEmpty() && floorsEmpty()){
		e.stopping();
		e.stepTimer();
		//std::cout << timer << std::endl;
		return;
	}
	if(e.getMotion() == Motion::Moving){
		if(e.getTimer() <= 0){
			e.passFloor();
			return;
		}
		if(e.isEmpty()){
			if(!floorEmpty(e.getFloor())){
				e.stopping();
				e.stepTimer();
				return;
			}
			e.stepTimer();
			return;
		}
		if(e.passengerCount() < 8 && floorHasPassengersInSameDirection(e.getFloor(), e.getDirection())){
			e.stopping();
			e.stepTimer();
			return;
		}
		if(e.passengerNeedsStop()){
			e.stopping();
			e.stepTimer();
			return;
		}
		e.stepTimer();
		return;

	}
	if(e.getMotion() == Motion::Stopping){
		if(e.getTimer() <= 0){
			e.stop();
			return;
		} else{
			e.stepTimer();
			return;
		}
	}
	if(e.getMotion() == Motion::Stopped){
		while(e.tryUnloadPassenger()){ //unboard all passengers possible
			int travelTime = timer - e.unboardPassenger().getStartTime();
			sumOfTravelTimes += travelTime;
			std::cout << timer << " " << travelTime << " " << e.getFloor() << " " << e.passengerCount() << std::endl;

		}
		while(e.addPassenger(&floors.at(e.getFloor()))){
		}
		if(!e.isEmpty()){
			e.startMoving(e.getDirection());
			return;
		}
		if(!floorsEmpty()){
			// Choose algorithm, could make this dynamic
			//e.startMoving(getOccupiedFloorDirection(e.getFloor()));
			//e.startMoving(getClosestOccupiedFloorDirection(e.getFloor()));
			e.startMoving(e.getDirection());
		}
		return;
	}

}

void ElevatorSim::strategy(Elevator &e)
{

}
