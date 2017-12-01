#include "sqltablemodel.h"

SqlTableModel::SqlTableModel(QObject *parent, Database *db) : QSqlRelationalTableModel(parent)
{
    this->setEditStrategy(QSqlRelationalTableModel::OnFieldChange);
}

QVariant SqlTableModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= rowCount())
    {
        return QString("");
    }
    if(role < Qt::UserRole)
    {
        return QSqlRelationalTableModel::data(index, role);
    }

    QModelIndex modelIndex = this->index(index.row(), role - Qt::UserRole - 1 );
    return QSqlRelationalTableModel::data(modelIndex, Qt::EditRole);
}

void SqlTableModel::setTable(const QString &table_name)
{
    QSqlRelationalTableModel::setTable(table_name);
    generateRoleNames();
}

QHash<int, QByteArray> SqlTableModel::roleNames() const
{
    return roles;
}

SqlTableModel::~SqlTableModel()
{

}

void SqlTableModel::generateRoleNames()
{
    roles.clear();
    for (int i = 0; i < columnCount(); i++)
    {
    roles[Qt::UserRole + i + 1] = QVariant(headerData(i, Qt::Horizontal).toString()).toByteArray();
    }
}
