#include "SqlQueryModel.h"

SqlQueryModel::SqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void SqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    QSqlQueryModel::setQuery(query, db);
    generateRoleNames();
    queryString = query;
}

void SqlQueryModel::setQuery(const QSqlQuery & query)
{
    QSqlQueryModel::setQuery(query);
    generateRoleNames();
    queryPrivate = query;
}

void SqlQueryModel::refreshSouvTable()
{
    setQuery(Database::getInstance()->getSouvenirs());
}

void SqlQueryModel::refreshNFC()
{
    setQuery(Database::getInstance()->getNFC());
}

void SqlQueryModel::refreshAFC()
{
    setQuery(Database::getInstance()->getAFC());
}

void SqlQueryModel::refreshTeamInfo()
{
    setQuery(Database::getInstance()->getTeamInfo());
}

void SqlQueryModel::refreshCapacity()
{
    setQuery(Database::getInstance()->getStadiumsBySeatingCapacity().query);
}

void SqlQueryModel::refreshOpenStadiums()
{
    setQuery(Database::getInstance()->getOpenStadiums());
}

void SqlQueryModel::refreshAllStadiums()
{
    setQuery(Database::getInstance()->getAllStadiums());
}

void SqlQueryModel::generateRoleNames()
{
    m_roleNames.clear();
    for( int i = 0; i < record().count(); i ++) {
        m_roleNames.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if(role < Qt::UserRole) {
        value = QSqlQueryModel::data(index, role);
    }
    else {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}
