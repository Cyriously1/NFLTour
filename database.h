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
#include <QFileDialog>
#include <QFile>

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

    /**
     * @brief getSearchTeam
     * @param arg1
     * @return
     */
    QSqlQuery getSearchTeam(const QString &arg1);

    /**
     * @brief getTeamTypes
     * @param index
     * @return
     */
    QSqlQuery getTeamTypes(const int index);

    /**
     * @brief getOpenStadiums
     * @return
     */
    QSqlQuery getOpenStadiums();

    /**
     * @brief getAllStadiums
     * @return
     */
    QSqlQuery getAllStadiums();

    /**
     * @brief getStadiumsBySeatingCapacity
     * @return
     */
    QSqlQuery getStadiumsBySeatingCapacity();

    /**
     * @brief getSouvenirs
     * @param souvenirIndicator
     * @return
     */
    QSqlQuery getSouvenirs(QString souvenirIndicator);

    /**
     * @brief sortTable
     * @param index
     * @param nflType
     * @return
     */
    QSqlQuery sortTable(int index, QString nflType);

    /**
     * @brief getAFC
     * @param arg1
     * @return
     */
    QSqlQuery getAFC(const QString &arg1);

    /**
     * @brief getNFC
     * @param arg1
     * @return
     */
    QSqlQuery getNFC(const QString &arg1);

    /**
     * @brief getAllDistances
     * @return
     */
    QSqlQuery getAllDistances();

    /**
     * @brief addSailors
     */
    void addSailors();

    /**
     * @brief moveRams
     */
    void moveRams();

    /**
     * @brief getTeamsTour
     * @return
     */
    std::vector<QString> getTeamsTour();

    /**
     * @brief getStadiumsVec
     * @return
     */
    std::vector<QString> getStadiumsVec();

private:
    // private constructor
    /**
     * @brief Database
     */
    Database();

    // instance of Database
    // created once on startup
    /**
     * @brief instance
     */
    static Database* instance;
};

#endif // DATABASE_H
