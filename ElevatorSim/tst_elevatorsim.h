#ifndef TST_ELEVATORSIM_H
#define TST_ELEVATORSIM_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>

#include <vector>

#include "elevatorutils.h"
#include "passenger.h"
#include "direction.h"
#include "floor.h"

using namespace testing;

TEST(newgt, newgtc)
{
	EXPECT_EQ(1, 1);
	ASSERT_THAT(0, Eq(0));
}

TEST(elevatorSim, elevatorUtilities){
	std::queue<Passenger> passengerQueue;
	elevatorutils::readCSV("Mod10_Assignment_Elevators.csv", passengerQueue);
	EXPECT_EQ(passengerQueue.front().getStartTime(), 41);

	std::vector<Floor> floors(101,Floor());

	while(!passengerQueue.empty()){
		floors[passengerQueue.front().getStartFloor()].addPassenger(passengerQueue.front());
		passengerQueue.pop();
	}

	EXPECT_EQ(floors[54].UpPassengers.front().getEndFloor(), 55);
	EXPECT_EQ(floors[42].UpPassengers.back().getEndFloor(), 76);
}

TEST(elevatorSim, passengerTest){
	Passenger p = Passenger(14,32,50);
	EXPECT_EQ(p.getDirection(), Direction::Up);
}

TEST(elevatorSim, floorTest){
	std::vector<Floor> floors(101,Floor());
	Passenger p = Passenger(14,32,50);
	floors[3].addPassenger(p);
	EXPECT_EQ(floors[3].UpPassengers.size(), 1);
}



#endif // TST_ELEVATORSIM_H
