/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "mymodel.h"

#include <QTableView>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDataStream>

#include "statistics.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tableView(new QTableView(this))
{

	MyModel* myModel;
	myModel = new MyModel();

    auto fileContentReady = [&myModel, this](const QString &fileName, const QByteArray &fileContent) {
		if (fileName.isEmpty()) {
			// No file was selected
			myModel = new MyModel(this);

		} else {
			// Use fileName and fileContent
            Statistics statData;
            QList<QByteArray> list = fileContent.split('\n');

            for(QString n : list){
                //std::cout << n.toStdString() << std::endl;
                statData.add(n.toDouble());
            }

            myModel = new MyModel(this, statData); // better to pass by reference
            tableView->setModel(myModel);
		}
	};
	QFileDialog::getOpenFileContent("Data file",  fileContentReady);

    tableView->setModel(myModel);

    //transfer changes to the model to the window title
    connect(myModel, &MyModel::editCompleted,
            this, &MainWindow::showWindowTitle);

	QAction * addItem = new QAction(tr("Add"), this);
	connect(addItem, &QAction::triggered, myModel, &MyModel::appendRow);

    QAction* openFile = new QAction(tr("Open File"), this);
    connect(openFile, &QAction::triggered,
            [=](){QFileDialog::getOpenFileContent("Data file", fileContentReady);});

	// get menu in view
	QMenu *fileMenu;
	fileMenu = menuBar()->addMenu(tr("&Edit"));
	fileMenu->addAction(addItem);
    fileMenu->addAction(openFile);

	QPushButton* addButton = new QPushButton(tr("Add Item"), this);
	connect(addButton, &QPushButton::clicked, myModel, &MyModel::appendRow);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(addButton);
	vLayout->addWidget(tableView);
	QWidget* statTable = new QWidget;
	statTable->setLayout(vLayout);
	setCentralWidget(statTable);


}

void MainWindow::showWindowTitle(const QString &title)
{
    setWindowTitle(title);
}
