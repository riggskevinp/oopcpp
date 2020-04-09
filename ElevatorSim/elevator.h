#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <list>

#include "direction.h"
#include "passenger.h"
#include "floor.h"

#include <QObject>
#include <QSlider>

enum class Motion{Moving,Stopping,Stopped};

class Elevator: public QObject
{
	Q_OBJECT
public:
	Elevator(Direction d = Direction::Up, int c_timebetweenfloors = 10, int c_floor = 0);
	void addPassenger(Passenger newPassenger);
	bool addPassenger(Floor *f);
	Passenger unboardPassenger();
	bool tryUnloadPassenger();
	Direction getDirection() const{return direction;}
	Motion getMotion() const{return motion;}
	void stop(){motion = Motion::Stopped;}
	void stepTimer() {timer--;}
	bool isEmpty(){return passengers.empty();}
	void startMoving(Direction d);
	int getFloor() const{return floor;}
	int getTimer() const{return timer;}
	void passFloor();
	bool passengerNeedsStop();
	void stopping();
	int passengerCount(){return passengers.size();}

signals:
	void floorChanged(int floor);

private:
	Direction direction;
	Motion motion;
	int timeBetweenFloors;
	int timeToStop = 2;
	//next floor a passenger could get off or on
	//could be the floor moving to or stopped at.
	int floor;
	int timer;
	std::list<Passenger> passengers;

};

#endif // ELEVATOR_H
