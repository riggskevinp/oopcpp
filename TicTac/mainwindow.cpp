#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tictactoe.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	auto ticwidg = new TicTacToe(this);
	this->setCentralWidget(ticwidg);

}

MainWindow::~MainWindow()
{
	delete ui;
}

