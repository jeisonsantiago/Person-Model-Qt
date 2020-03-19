/*******************************************************************************
 *  Project: Person Model Qt
 *  Purpose: QAbstractListModel example
 *  Author: Jeison Santiago, jeison.santiago@gmail.com
 *  Language: C++
 *******************************************************************************
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2020 Jeison Santiago
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *******************************************************************************/


#include "PersonModel.h"

PersonModel::PersonModel(QObject *parent) : QAbstractListModel(parent)
{

}

void PersonModel::addPerson(Person *person)
{
    const int index = m_persons.size();
    person->setParent(this);
    beginInsertRows(QModelIndex(),index,index);
    m_persons.append(person);
    endInsertRows();

}

void PersonModel::addPerson()
{
    Person *person = new Person("Added Person",45,this);
    this->addPerson(person);
}

void PersonModel::addPerson(const QString &name, const int &age)
{
    Person *person = new Person(name,age,this);
    this->addPerson(person);
}

void PersonModel::removePerson(QModelIndex index)
{
    beginRemoveRows(QModelIndex(),index.row(),index.row());
    delete m_persons.takeAt(index.row());
    endRemoveRows();
}

int PersonModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_persons.size();
}

QVariant PersonModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_persons.count())
        return QVariant();

    Person * person = m_persons[index.row()];
    if(role == Qt::DisplayRole){
        return  person->name();
    }

    if(role == Qt::ToolTipRole){
        return  person->name() + " age:" + QString::number(person->age());
    }
    return  QVariant();

}

bool PersonModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) {
        return false;
    }

    bool somethingChanged = false;

    switch (role) {
        case Qt::DisplayRole:
        {
            m_persons[index.row()]->setValues(value);
            somethingChanged = true;
            break;
        }
    }

    if(somethingChanged){
        emit dataChanged(index,index);
        return true;
    }

    return false;

}

Qt::ItemFlags PersonModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QAbstractItemModel::flags(index) | Qt::ItemIsDropEnabled;
    }

    return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled;
}

bool PersonModel::canDropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(parent);

    if (!data->hasFormat("material_data"))
        return false;

    if (column > 0)
        return false;

    return true;
}

bool PersonModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    // simple work around for the drop "out side" of the drop indicator zone
    if(row == -1) row = rowCount();

    if(data->hasFormat("material_data")){
        if(parent.isValid()){
            //Replace data
            this->insertRows(rowCount(),1,QModelIndex());
            this->setData(index(rowCount()-1),data->data("material_data"),Qt::DisplayRole);
        }
        else{
            //Add new data
            this->insertRows(row,1,QModelIndex());
            this->setData(index(row),data->data("material_data"),Qt::DisplayRole);
        }
        return true;
    }
    return QAbstractListModel::dropMimeData(data,action,row,column,parent);
}

Qt::DropActions PersonModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}


Qt::DropActions PersonModel::supportedDragActions() const
{
    return Qt::MoveAction;
}


QStringList PersonModel::mimeTypes() const
{
    return QAbstractListModel::mimeTypes() << "material_data";
}

QMimeData *PersonModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData * mimeData = QAbstractListModel::mimeData(indexes);
    QByteArray encodedData;
    QDataStream stream(&encodedData,QIODevice::WriteOnly);

    for( const QModelIndex & index : indexes){
        if(index.isValid()){
            stream << m_persons[index.row()]->getValues();
        }
    }

    mimeData->setData("material_data",encodedData);
    return mimeData;
}

bool PersonModel::insertRows(int row, int count = 0, const QModelIndex &parent = QModelIndex())
{
    qDebug() << "insertRows()";
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row+count-1);

    for (int i = 0; i < count; ++i) {
        m_persons.insert(row,new Person(this));
    }
    endInsertRows();
    return  true;
}

bool PersonModel::removeRows(int row, int count, const QModelIndex &parent)
{
    qDebug() << "removeRows()";
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row+count-1);

    for (int i = 0; i < count; ++i) {
        delete m_persons.takeAt(row);
    }
    endRemoveRows();
    return true;
}

