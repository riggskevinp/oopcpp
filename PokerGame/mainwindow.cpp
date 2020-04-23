#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

#include <vector>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

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
			QSpinBox *sb = new QSpinBox(this);
			QPushButton *betButton = new QPushButton(QString("Bet"),this);
			QPushButton *foldButton = new QPushButton(QString("Fold"),this);
			QLabel *handLabel = new QLabel(this);
			ui->gridLayout->addWidget(chipsLabel,ui->gridLayout->rowCount(),0);
			ui->gridLayout->addWidget(sb,ui->gridLayout->rowCount()-1,1);
			ui->gridLayout->addWidget(betButton,ui->gridLayout->rowCount()-1,2);
			ui->gridLayout->addWidget(foldButton,ui->gridLayout->rowCount()-1,3);
			ui->gridLayout->addWidget(handLabel,ui->gridLayout->rowCount()-1,4);
		}
		for(int i = 0; i < (numberOfPlayers - numberOfHumans); i++){
			QLabel *chipsLabel = new QLabel(this);
			QLabel *betLabel = new QLabel(this);
			QLabel *statusLabel = new QLabel(this);
			QLabel *handLabel = new QLabel(this);
			ui->gridLayout->addWidget(chipsLabel,ui->gridLayout->rowCount(),0);
			ui->gridLayout->addWidget(betLabel,ui->gridLayout->rowCount()-1,1);
			ui->gridLayout->addWidget(statusLabel,ui->gridLayout->rowCount()-1,2);
			ui->gridLayout->addWidget(handLabel,ui->gridLayout->rowCount()-1,4);
		}

	});


	//ui->label->setText(QString("Value of hand: %1").arg(hand.getValue(),0,'f', 12));

}

MainWindow::~MainWindow()
{
	delete pg;
	delete ui;
}

