#ifndef SLOTOBJECT_H
#define SLOTOBJECT_H

#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sqlquerymodel.h"
#include "database.h"
#include "sqltablemodel.h"

class SlotObject : public QObject
{
    Q_OBJECT
public:
    explicit SlotObject(QObject *parent = nullptr);
private:
    Database *database = Database::getInstance();
    QString input;

signals:

public slots:
    void cppSlot(const QString &msg)
    {
        qDebug() << "Called the C++ slot with message: " << msg;
        input = msg;
    }

    void addSailors()
    {
        qDebug() << "C++ Sailors added.";
        Database::getInstance()->addSailors(input);
    }

    void moveRams()
    {
        qDebug() << "C++ Rams moved.";
        Database::getInstance()->moveRams();
    }
    void setInput(QString msg)
    {
        qDebug() << "C++ input message set to: " << msg;
        input = msg;
    }
    void addSouvenir(QString stadiumName, QString newSouvName, QString newSouvPrice)
    {
        qDebug() << "C++ addSouvenir called with... ";
        qDebug() << stadiumName;
        qDebug() << newSouvName;
        qDebug() << newSouvPrice;

        Database::getInstance()->addSouvenir(stadiumName, newSouvName, newSouvPrice);
    }
    void removeRow(QString stadium, QString name)
    {
        qDebug() << "C++ removeThisRow() called with...";
        qDebug() << stadium;
        qDebug() << name;

        Database::getInstance()->removeSouvenir(stadium,name);
    }
};

#endif // SLOTOBJECT_H
