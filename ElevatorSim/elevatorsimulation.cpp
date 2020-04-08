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

void ElevatorSim::operate(Elevator &e)
{
	/*
	if(e.motion == Motion::Moving){

	}
	if(e.motion == Motion::Stopping){
		if(e.timer <= 0){
			e.motion = Motion::Stopped;
			return;
		} else{
			e.timer--;
			return;
		}
	}
	if(e.motion == Motion::Stopped){
		if(e.floor == e.passengers.front().getEndFloor()){
			sumOfTravelTimes += (timer - e.unboardPassenger()
		}
	}
	*/
}
