#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <vector>
#include <queue>

#include "elevatorutils.h"
#include "passenger.h"
#include "elevator.h"
#include "floor.h"

class ElevatorSim
{
public:
	ElevatorSim();
	int run(); // run simulation, return average trip time as an int?

private:
	void operate(Elevator &e);
	std::queue<Passenger> passengerQueue;
	std::vector<Floor> floors;
	std::vector<Elevator> elevators;
	int timer;
	int sumOfTravelTimes;
};

#endif // ELEVATORSIMULATION_H
