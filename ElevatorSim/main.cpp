#include "mainwindow.h"
#include <QApplication>

#include <gtest/gtest.h>
#include "tst_elevatorsim.h"

#include <QProcess>
#include <QThread>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	//w.runSimulation();
    return a.exec();
}
