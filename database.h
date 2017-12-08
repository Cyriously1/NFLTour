#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QSqlField>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <vector>
#include <QString>
#include <QFile>

struct capTable
{
    QSqlQuery query;
    int       total;
};

/** Database
 * - Singleton
 * - Inherits from QSqlDatabase
 */
class Database: public QSqlDatabase
{
public:
    static Database* getInstance();

    /**
     * @brief getTeamInfo
     * @return query of all items in TeamInfo table
     */
    QSqlQuery getTeamInfo();
    QSqlQuery getSearchTeam(const QString &arg1);
    QSqlQuery getTeamTypes(const int index);
    QSqlQuery getOpenStadiums();
    QSqlQuery getAllStadiums();
    capTable getStadiumsBySeatingCapacity();
    QSqlQuery getSouvenirs();
    QSqlQuery sortTable(int index);
    QSqlQuery getAFC();
    QSqlQuery getNFC();
    void addSailors(QString input);
    void moveRams();
    void addSouvenir(QString stadiumName, QString newSouvName, QString newSouvPrice);
    void removeSouvenir(QString stadium, QString name);
    int displayOpenStadiums();

private:
    // private constructor
    Database();

    // instance of Database
    // created once on startup
    static Database* instance;
};

#endif // DATABASE_H
