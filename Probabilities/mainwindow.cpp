#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}

