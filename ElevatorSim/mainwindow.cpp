#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "elevatorsimulation.h"
#include "elevator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
	//, sim(ElevatorSim(ui->textEdit))
{
	ui->setupUi(this);
	sim = ElevatorSim(ui->textEdit);

	// resource management should be implemented better
	//ElevatorSim sim = ElevatorSim();
	Elevator *a = new Elevator();
	Elevator *b = new Elevator(Direction::Up, 10, 0);
	Elevator *c = new Elevator(Direction::Up, 10, 0);
	Elevator *d = new Elevator(Direction::Up, 10, 0);

	connect(a, &Elevator::floorChanged, ui->verticalSlider, &QSlider::setValue);
	connect(b, &Elevator::floorChanged, ui->verticalSlider_2, &QSlider::setValue);
	connect(c, &Elevator::floorChanged, ui->verticalSlider_3, &QSlider::setValue);
	connect(d, &Elevator::floorChanged, ui->verticalSlider_4, &QSlider::setValue);

	sim.addElevator(a);
	sim.addElevator(b);
	sim.addElevator(c);
	sim.addElevator(d);


	connect(ui->pushButton, &QPushButton::clicked,[this](){
		ui->label_2->setText(QString("%1 seconds").arg(this->sim.run()));
		});





}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::runSimulation()
{
	sim.run();
}


