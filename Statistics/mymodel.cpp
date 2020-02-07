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

#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

MyModel::MyModel(QObject *parent, Statistics stats)
	: QAbstractTableModel(parent),
	  m_items(stats)
{

}


QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole && orientation == Qt::Vertical)
		{
			if(section == 0) {
				return QString("Average");
			} else if(section == 1){
				return QString("STD Dev");
			} else {
				return QString("%1").arg(section - 1);
			}
		}
	return QVariant();
}



int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
    return m_items.getItemCount() + ROWS;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return COLS;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole && checkIndex(index)){
		if(index.row() == 1){
			return m_items.getSTD();
		}
		else if(index.row() == 0){
			return m_items.getAverage();
		}
		else{
			return m_items.getItem(index.row() - 2);
		}
	}

    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        m_items.setItem(index.row() - 2, value.toDouble());
        return true;
    }
    return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    // add case for STD and Average, make not editable
	if(index.row() == 0 || index.row() == 1){
		return QAbstractTableModel::flags(index);
	} else{
		return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
	}
}

bool MyModel::insertRows(int position, int rows, const QModelIndex &index)
{
	Q_UNUSED(index);
		beginInsertRows(QModelIndex(), this->rowCount(), this->rowCount());
		m_items.add(0.0);
		endInsertRows();
		return true;
}

void MyModel::appendRow()
{
	this->insertRows(this->rowCount()-1,1);
}

