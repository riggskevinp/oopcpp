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
	int numberOfPassengers = passengerQueue.size();

	for(timer = 0; timer <= 30000; timer++){
		while(passengerQueue.front().getStartTime() >= timer){
			floors[passengerQueue.front().getStartFloor()].addPassenger(passengerQueue.front());
			passengerQueue.pop();
		}

		for(auto &e : elevators){
			operate(e);
		}
	}
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

void ElevatorSim::operate(Elevator &e)
{
	if(e.getMotion() == Motion::Moving){
		if(e.getTimer() <= 0){
			e.passFloor();
		}
		if(e.passengerNeedsStop()){
			e.stopping();
			e.stepTimer();
		}

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
			sumOfTravelTimes += (timer - e.unboardPassenger().getStartTime());
		}
		while(e.addPassenger(&floors.at(e.getFloor()))){

		}
		if(!e.isEmpty()){
			e.startMoving(e.getDirection());
			return;
		}else if(!floorsEmpty()){
			e.startMoving(getOccupiedFloorDirection(e.getFloor()));
		}else{
			return;
		}

	}

}
