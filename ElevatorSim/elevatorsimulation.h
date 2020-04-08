#ifndef ELEVATORSIMULATION_H
#define ELEVATORSIMULATION_H

#include <vector>
#include <queue>

#include "passenger.h"
#include "elevator.h"
#include "floor.h"
#include "elevatorutils.h"

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

#endif // ELEVATORSIM_H
