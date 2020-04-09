#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <vector>
#include <queue>

#include "elevatorutils.h"
#include "passenger.h"
#include "elevator.h"
#include "floor.h"
#include "direction.h"

class ElevatorSim
{
public:
	ElevatorSim();
	int run(); // run simulation, return average trip time as an int?
	void addElevator(Elevator e){elevators.push_back(e);}



private:
	bool floorsEmpty();
	bool floorEmpty(int floor);
	Direction getOccupiedFloorDirection(int floorNumber);
	//could add a getNextOccupiedFloorDirection()
	void operate(Elevator &e);
	std::queue<Passenger> passengerQueue;
	std::vector<Floor> floors;
	std::vector<Elevator> elevators;
	int timer;
	int sumOfTravelTimes;
	int passengersAtDestination;
};

#endif // ELEVATORSIMULATION_H
