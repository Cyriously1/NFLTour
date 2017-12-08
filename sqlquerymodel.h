#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include "database.h"

class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SqlQueryModel(QObject *parent = 0);

    void setQuery(const QString &query, const QSqlDatabase &db = QSqlDatabase());
    void setQuery(const QSqlQuery &query);
    Q_INVOKABLE void refreshSouvTable();
    Q_INVOKABLE void refreshNFC();
    Q_INVOKABLE void refreshAFC();
    Q_INVOKABLE void refreshTeamInfo();
    Q_INVOKABLE void refreshCapacity();
    Q_INVOKABLE void refreshOpenStadiums();
    Q_INVOKABLE void refreshAllStadiums();
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const {	return m_roleNames;	}

private:
    void generateRoleNames();
    QHash<int, QByteArray> m_roleNames;
    QString queryString;
    QSqlQuery queryPrivate;
};

#endif // SQLQUERYMODEL_H
