#ifndef SQLTABLEMODEL_H
#define SQLTABLEMODEL_H

#include "QSqlRelationalTableModel"
#include "database.h"
#include <QObject>

class SqlTableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
//    Q_PROPERTY(int count READ rowCount() NOTIFY countChanged())

signals:
    void countChanged();
private:
    QHash<int, QByteArray> roles;
    int count;

public:
    SqlTableModel(QObject *parent = 0, Database *db = Database::getInstance());
    ~SqlTableModel();
    void generateRoleNames();
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;
    virtual void setTable ( const QString &table_name );
    virtual QHash<int, QByteArray> roleNames() const;
};

#endif // SQLTABLEMODEL_H
