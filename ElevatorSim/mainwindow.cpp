#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "elevatorsimulation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	ElevatorSim sim = ElevatorSim();

}

MainWindow::~MainWindow()
{
    delete ui;
}


