#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSpinBox>
#include <vector>
#include <tuple>

#include "pokergame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void humanBetChanged();
	void deal();
	void showHands();
	void betChanged(int bet);

private:
	Ui::MainWindow *ui;
	PokerGame *pg;
	QStringList faces = {"2","3","4","5","6","7","8","9","T","J","Q","K","A"};
	QStringList suits = {"H","C","D","S"};
	int currentBet = 0;
	std::vector<std::tuple<QLabel*, QSpinBox*,QLabel*>> humanPlayers;
	std::vector<std::tuple<QLabel*,QLabel*,QLabel*>> computerPlayers;
};
#endif // MAINWINDOW_H
