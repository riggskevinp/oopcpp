#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "elevatorsimulation.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	// resource management should be implemented better
	ElevatorSim sim = ElevatorSim();
	Elevator a = Elevator();
	Elevator b = Elevator(Direction::Up, 10, 20);
	Elevator c = Elevator(Direction::Up, 10, 40);
	Elevator d = Elevator(Direction::Up, 10, 60);
	//Elevator(Direction d = Direction::Up, int c_timebetweenfloors = 10, int c_floor = 0
	sim.addElevator(a);
	sim.addElevator(b);
	sim.addElevator(c);
	sim.addElevator(d);
	int averageTravelTime = sim.run();





}

MainWindow::~MainWindow()
{
    delete ui;
}


