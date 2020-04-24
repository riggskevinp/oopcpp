#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>


#include <vector>

#include "player.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->dealButton->setDisabled(true);
	ui->showCardsButton->setDisabled(true);

	connect(ui->dealButton, &QPushButton::clicked, this, &MainWindow::deal);
	connect(ui->showCardsButton, &QPushButton::clicked, this, &MainWindow::showHands);
	connect(ui->NewGameButton, &QPushButton::clicked, [this](){
		ui->NewGameButton->setDisabled(true);

		int numberOfPlayers = ui->numberOfPlayersSpinBox->value();
		int numberOfHumans = ui->numberOfHumansSpinBox->value();
		if(numberOfPlayers < numberOfHumans){
			numberOfPlayers = numberOfHumans;
			ui->numberOfPlayersSpinBox->setValue(numberOfPlayers);
		}
		ui->numberOfHumansSpinBox->setDisabled(true);
		ui->numberOfPlayersSpinBox->setDisabled(true);
		pg =  new PokerGame(numberOfPlayers);

		for(int i = 0; i < numberOfHumans; i++){
			QLabel *chipsLabel = new QLabel(this);
			chipsLabel->setNum(pg->players.at(i)->getChipCount());
			QSpinBox *sb = new QSpinBox(this);
			connect(sb, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::betChanged);
			QLabel *handLabel = new QLabel(this);
			handLabel->setText(QString("Empty"));
			ui->gridLayout->addWidget(chipsLabel,ui->gridLayout->rowCount(),0);
			ui->gridLayout->addWidget(sb,ui->gridLayout->rowCount()-1,1);
			ui->gridLayout->addWidget(handLabel,ui->gridLayout->rowCount()-1,2);
			humanPlayers.push_back(std::make_tuple(chipsLabel,sb,handLabel));
		}
		for(int i = 0; i < (numberOfPlayers - numberOfHumans); i++){
			QLabel *chipsLabel = new QLabel(this);
			chipsLabel->setNum(pg->players.at(i+numberOfHumans)->getChipCount());
			QLabel *betLabel = new QLabel(this);
			betLabel->setNum(0);
			betLabel->setDisabled(true);
			QLabel *statusLabel = new QLabel(this);
			QLabel *handLabel = new QLabel(this);
			handLabel->setText(QString("Empty"));
			ui->gridLayout->addWidget(chipsLabel,ui->gridLayout->rowCount(),0);
			ui->gridLayout->addWidget(betLabel,ui->gridLayout->rowCount()-1,1);
			ui->gridLayout->addWidget(handLabel,ui->gridLayout->rowCount()-1,2);
			computerPlayers.push_back(std::make_tuple(chipsLabel,betLabel,handLabel));
		}
		ui->dealButton->setEnabled(true);

	});


	//ui->label->setText(QString("Value of hand: %1").arg(hand.getValue(),0,'f', 12));

}

MainWindow::~MainWindow()
{
	delete pg;
	delete ui;
}

void MainWindow::deal()
{
	this->ui->dealButton->setDisabled(true);
	pg->deal();
	for(int i = 0; i < humanPlayers.size(); i++){
		std::get<0>(humanPlayers.at(i))->setNum(pg->players.at(i)->getChipCount());
		std::get<1>(humanPlayers.at(i))->setValue(0);
		std::get<1>(humanPlayers.at(i))->setEnabled(true);
		auto c = pg->players.at(i)->showCards();
		std::get<2>(humanPlayers.at(i))->setText(QString("%1%2 %3%4 %5%6 %7%8 %9%10").arg(faces.at(c.at(0).getFace())).arg(suits.at(c.at(0).getSuit()))
																						.arg(faces.at(c.at(1).getFace())).arg(suits.at(c.at(1).getSuit()))
																						.arg(faces.at(c.at(2).getFace())).arg(suits.at(c.at(2).getSuit()))
																						.arg(faces.at(c.at(3).getFace())).arg(suits.at(c.at(3).getSuit()))
																						.arg(faces.at(c.at(4).getFace())).arg(suits.at(c.at(4).getSuit())));

	}
	for(int i = 0; i < computerPlayers.size(); i++){
		std::get<0>(computerPlayers.at(i))->setNum(pg->players.at(i + humanPlayers.size())->getChipCount());
		std::get<1>(computerPlayers.at(i))->setNum(0);
		std::get<2>(computerPlayers.at(i))->setText(QString("** ** ** ** **"));
	}
	ui->potLabel->setNum(pg->pot);
	this->ui->showCardsButton->setEnabled(true);
}

void MainWindow::showHands()
{
	ui->showCardsButton->setDisabled(true);
	// take bets from human players, handle folds
	for(int i = 0; i < humanPlayers.size(); i++){
		std::get<1>(humanPlayers.at(i))->setDisabled(true);
		if(currentBet > std::get<1>(humanPlayers.at(i))->value()){
			pg->players.at(i)->fold();
		} else{
			pg->pot += pg->players.at(i)->bet(currentBet);
		}
	}
	ui->potLabel->setNum(pg->pot);
	// display computer hands
	for(int i = 0; i < computerPlayers.size(); i++){
		auto c = pg->players.at(i+humanPlayers.size())->showCards();
		std::get<2>(computerPlayers.at(i))->setText(QString("%1%2 %3%4 %5%6 %7%8 %9%10").arg(faces.at(c.at(0).getFace())).arg(suits.at(c.at(0).getSuit()))
																						.arg(faces.at(c.at(1).getFace())).arg(suits.at(c.at(1).getSuit()))
																						.arg(faces.at(c.at(2).getFace())).arg(suits.at(c.at(2).getSuit()))
																						.arg(faces.at(c.at(3).getFace())).arg(suits.at(c.at(3).getSuit()))
																						.arg(faces.at(c.at(4).getFace())).arg(suits.at(c.at(4).getSuit())));

	}
	// update winners
	pg->showHands();
	for(int i = 0; i < humanPlayers.size(); i++){
		std::get<0>(humanPlayers.at(i))->setNum(pg->players.at(i)->getChipCount());
	}
	for(int i = 0; i < computerPlayers.size(); i++){
		std::get<0>(computerPlayers.at(i))->setNum(pg->players.at(i + humanPlayers.size())->getChipCount());
	}

	ui->dealButton->setEnabled(true);
}

void MainWindow::betChanged(int bet)
{
	if(bet > currentBet){
		// Current Computer Strategy: in it to win it
		for(int i = 0; i < computerPlayers.size(); i++){
			pg->pot += pg->players.at(humanPlayers.size()+i)->bet(bet - currentBet);
			std::get<0>(computerPlayers.at(i))->setNum(pg->players.at(i + humanPlayers.size())->getChipCount());
			std::get<1>(computerPlayers.at(i))->setNum(bet);
			ui->potLabel->setNum(pg->pot);
		}
		// Alternative Computer Strategy: use the absolute value of its hand to limit how much it will bet
		// along with a random amount of discretion(pseudo bluff)
		currentBet = bet;
	}
}

