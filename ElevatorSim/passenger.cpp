#include "passenger.h"

Passenger::Passenger(int t_startTime, int t_startFloor, int t_endFloor):
	StartTime(t_startTime),
	EndTime(-1),
	StartFloor(t_startFloor),
	EndFloor(t_endFloor){
	int def = t_endFloor - t_startFloor;
	if(def == 0){
		throw;
	}
	else if (def > 0) {
		direction = Direction::Up;
	} else{
		direction = Direction::Down;
	}
}
