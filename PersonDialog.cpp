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

#include "PersonDialog.h"

PersonDialog::PersonDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("Person Dialog");

    QLabel *m_nameLabel = new QLabel("Name:",this);
    m_gridLayout = new QGridLayout(this);


    QLabel *m_ageLabel = new QLabel("Age:",this);
    m_lineEditName = new QLineEdit(this);

    m_spinBoxAge = new QSpinBox(this);
    m_spinBoxAge->setRange(1,200);

    m_okButtom = new QPushButton("OK",this);
    m_cancelButtom = new QPushButton("Cancel",this);

    m_buttomGroup = new QFrame(this);

    this->setLayout(m_gridLayout);

    m_gridLayout->addWidget(m_nameLabel,0,0);
    m_gridLayout->addWidget(m_lineEditName,0,1);

    m_gridLayout->addWidget(m_ageLabel,1,0);
    m_gridLayout->addWidget(m_spinBoxAge,1,1);

    QHBoxLayout *pvLayout = new QHBoxLayout(this);
    m_buttomGroup->setLayout(pvLayout);
    pvLayout->addWidget(m_okButtom);
    pvLayout->addWidget(m_cancelButtom);

    m_gridLayout->addWidget(m_buttomGroup,2,0,1,2);
    connect(m_okButtom,&QPushButton::clicked,this,&PersonDialog::okClicked);
}

// I would implement the QDialog::Accepted/Rejected but this feels right.
QPair<QString,int> PersonDialog::execute()
{
    this->exec();
    QPair<QString,int> res;
    if(m_lineEditName->text().isEmpty())
        return QPair<QString,int>();

    res.first = m_lineEditName->text();
    res.second = m_spinBoxAge->value();
    return res;
}


// since we are not evaluating exec() I can call close XD
void PersonDialog::okClicked()
{
    this->close();
}
