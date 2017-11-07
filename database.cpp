#include "database.h"

// Instance is initially null
Database* Database::instance = nullptr;

/**
 * @brief Database::getInstance
 *
 * returns a pointer to Database
 * If one is not created, one is created
 *
 * @return instance
 */
Database* Database::getInstance() {
    if (instance == nullptr)
        instance = new Database;

    return instance;
}

/**
 * @brief Database::Database
 * creates a connection to a SQLite database file.  Verfies that
 * it is open
 */
Database::Database(): QSqlDatabase(addDatabase("QSQLITE")) {
    QDir dir(QDir::currentPath()); //gets current path
    QString current;//holds new path


    // ..cd up to parent directory
    while(dir.dirName() != "NFLTour") {
        dir.cdUp();
    }

    //adds path to database
    current = dir.absolutePath() + "/Database/NFLDB.db";
    qDebug() << "Path is " + current;

    //sets database path
    setDatabaseName(current);
    QFileInfo existingDatabaseInfo(current);

    //outputs if path exists
    if (existingDatabaseInfo.exists())
    {
        qDebug() << "Database file is open\n";
        open();
    }
    else
        qDebug() << "Datebase file is not open\n";
}


QSqlQuery Database::getTeamInfo() {
    QSqlQuery query(*this);
    std::vector<QString> vec;

    query.prepare("SELECT * FROM NFLInformation");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }

    return query;
}

QSqlQuery Database::getSearchTeam(const QString &arg1) {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE LOWER(TeamName) LIKE '%"+arg1.toLower()+"%'");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}


QSqlQuery Database::getTeamTypes(const int index) {

    QSqlQuery query(*this);

    switch (index)
    {
    case 0:
        query = getTeamInfo();
        break;
    case 1:
        query.exec("SELECT * FROM NFLInformation WHERE Conference = 'American Football Conference'");
        break;
    case 2:
        query.exec("SELECT * FROM NFLInformation WHERE Conference = 'National Football Conference'");
        break;
    }

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}



