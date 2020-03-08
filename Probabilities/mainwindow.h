#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QPieSeries>
#include "probabilities.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateProbabilities();

private:
    Ui::MainWindow *ui;
    Probabilities A;
    Probabilities B;
    QtCharts::QPieSeries *series3;
    QtCharts::QChart *chart3;
};
#endif // MAINWINDOW_H
