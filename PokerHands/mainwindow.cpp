#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include "pokerhand.h"

#include <vector>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QStringList faces = {"2","3","4","5","6","7","8","9","T","J","Q","K","A"};
	QStringList suits = {"H","C","D","S"};
	ui->comboBox->addItems(suits);
	ui->comboBox_3->addItems(suits);
	ui->comboBox_5->addItems(suits);
	ui->comboBox_7->addItems(suits);
	ui->comboBox_9->addItems(suits);
	ui->comboBox_2->addItems(faces);
	ui->comboBox_4->addItems(faces);
	ui->comboBox_6->addItems(faces);
	ui->comboBox_8->addItems(faces);
	ui->comboBox_10->addItems(faces);

	connect(ui->pushButton, &QPushButton::clicked, [this](){

		Card card1 = Card(ui->comboBox->currentText().at(0).toLatin1(),ui->comboBox_2->currentText().at(0).toLatin1());
		Card card2 = Card(ui->comboBox_3->currentText().at(0).toLatin1(),ui->comboBox_4->currentText().at(0).toLatin1());
		Card card3 = Card(ui->comboBox_5->currentText().at(0).toLatin1(),ui->comboBox_6->currentText().at(0).toLatin1());
		Card card4 = Card(ui->comboBox_7->currentText().at(0).toLatin1(),ui->comboBox_8->currentText().at(0).toLatin1());
		Card card5 = Card(ui->comboBox_9->currentText().at(0).toLatin1(),ui->comboBox_10->currentText().at(0).toLatin1());

		std::vector<Card> cardVec;
		cardVec.push_back(card1);
		cardVec.push_back(card2);
		cardVec.push_back(card3);
		cardVec.push_back(card4);
		cardVec.push_back(card5);

		PokerHand hand = PokerHand(cardVec);

		ui->label->setText(QString("Value of hand: %1").arg(hand.getValue(),0,'f', 12));

	});

}

MainWindow::~MainWindow()
{
	delete ui;
}

