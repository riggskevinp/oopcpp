#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <vector>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//ui->label->setText(QString("Value of hand: %1").arg(hand.getValue(),0,'f', 12));

}

MainWindow::~MainWindow()
{
	delete ui;
}

