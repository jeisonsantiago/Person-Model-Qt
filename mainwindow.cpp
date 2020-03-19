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


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_materialModel = new PersonModel(this);
    m_materialModel->addPerson("Jack",34);
    m_materialModel->addPerson("Raymond",30);
    m_materialModel->addPerson("Amela",1);
    m_materialModel->addPerson("Joseph",34);
    m_materialModel->addPerson("Katrina",29);

    this->initGUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRemove_clicked()
{
    QModelIndex index = ui->listView->currentIndex();

    if(index.isValid())
        m_materialModel->removePerson(index);
}

void MainWindow::on_pushButtonAdd_clicked()
{
    PersonDialog *personDialog = new PersonDialog(this);
    QPair<QString,int> res = personDialog->execute();

    if(!res.first.isEmpty()){
        m_materialModel->addPerson(res.first,res.second);
    }

    delete  personDialog;
}

void MainWindow::initGUI()
{

    QRect screenGeometry = QGuiApplication::screens().first()->geometry();
    int x = (screenGeometry.width()) / 2;
    int y = (screenGeometry.height()) / 2;
    this->move(x-(this->width()/2), y-(this->height()/2));

    ui->listView->setModel(m_materialModel);

    ui->listView->setDragEnabled(true);
    ui->listView->setDropIndicatorShown(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
}
