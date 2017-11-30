#ifndef SLOTOBJECT_H
#define SLOTOBJECT_H

#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "sqlquerymodel.h"
#include "database.h"

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
};

#endif // SLOTOBJECT_H
