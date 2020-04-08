#ifndef PASSENGER_H
#define PASSENGER_H

#include "direction.h"

class Passenger
{
public:
	explicit Passenger(int t_startTime, int t_startFloor, int t_endFloor);
	int getStartTime() const{return StartTime;}
	int getStartFloor() const{return StartFloor;}
	int getEndFloor() const{return EndFloor;}
	Direction getDirection(){return direction;}
	void setEndTime(int time){EndTime = time;}
	int getEndTime() const{return EndTime;}


private:
	int StartTime;
	int EndTime;
	int StartFloor;
	int EndFloor;
	Direction direction;

};

#endif // PASSENGER_H
