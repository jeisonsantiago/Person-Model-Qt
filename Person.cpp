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

#include "Person.h"

Person::Person(QObject *parent) : QObject(parent){}

Person::Person(QString name, int age, QObject *parent): QObject(parent), m_name(name.trimmed()), m_age(age){}

Person::~Person()
{
    qDebug() << "delete Person:" << m_name << m_age;
}

QString Person::name() const
{
    return m_name;
}

void Person::setName(const QString &name)
{
    m_name = name;
}

int Person::age() const
{
    return m_age;
}

void Person::setAge(int age)
{
    m_age = age;
}

// work with Json and just remove the 4 first bytes..I know...dirty af
QByteArray Person::getValues()
{
    QByteArray array;
    QJsonObject obj;
    obj.insert("name",this->m_name);
    obj.insert("age",this->m_age);

    array = QJsonDocument(obj).toJson(QJsonDocument::Compact);

    return array;
}

// same as above...
void Person::setValues(const QVariant &value)
{
    QJsonObject obj = QJsonDocument::fromJson(value.toByteArray().remove(0,4)).object();

    this->m_name = obj.value("name").toString();
    this->m_age = obj.value("age").toInt();
}
