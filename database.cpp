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

    query.prepare("SELECT * FROM NFLInformation ORDER BY NFLInformation.TeamName ASC");

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

QSqlQuery Database::getAFC(const QString &arg1) {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE LOWER(TeamName) LIKE '%"+arg1.toLower()+"%' AND Conference = 'American Football Conference'");


    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QSqlQuery Database::getNFC(const QString &arg1) {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE LOWER(TeamName) LIKE '%"+arg1.toLower()+"%' AND Conference = 'National Football Conference'");


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
        query.exec("SELECT * FROM NFLInformation WHERE Conference = 'American Football Conference' "
                   "ORDER BY NFLInformation.TeamName ASC");
        break;
    case 2:
        query.exec("SELECT * FROM NFLInformation WHERE Conference = 'National Football Conference' "
                   "ORDER BY NFLInformation.TeamName ASC");
        break;
    }

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QSqlQuery Database::getAllStadiums() {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation "
                  "ORDER BY NFLInformation.StadiumName ASC");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QSqlQuery Database::getOpenStadiums() {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE NFLInformation.StadiumRoofType = 'Open' "
                  "ORDER BY NFLInformation.TeamName ASC");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QSqlQuery Database::getStadiumsBySeatingCapacity() {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation ORDER BY NFLInformation.SeatingCapacity ASC");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QSqlQuery Database::sortTable(int index, QString nflType) {
    QSqlQuery query(*this);

    QString sortingIndicator = "";

    qDebug() << index;
    switch(index) {
        case 1:
            sortingIndicator = "TeamName";
            break;
        case 2:
            sortingIndicator = "StadiumName";
            break;
        case 3:
            sortingIndicator = "SeatingCapacity";
            break;
        case 4:
            sortingIndicator = "Location";
            break;
        case 5:
            sortingIndicator = "Conference";
            break;
        case 6:
            sortingIndicator = "SurfaceType";
            break;
        case 7:
            sortingIndicator = "StadiumRoofType";
            break;
        case 8:
            sortingIndicator = "StarPlayer";
            break;
    }

    if(nflType == "AFC") {

        query.prepare("SELECT * FROM NFLInformation  WHERE Conference = 'American Football Conference' "
                      "ORDER BY NFLInformation.'"+sortingIndicator+"'");

    } else if(nflType == "NFC") {

        query.prepare("SELECT * FROM NFLInformation  WHERE Conference = 'National Football Conference' "
                      "ORDER BY NFLInformation.'"+sortingIndicator+"'");

    } else {

        query.prepare("SELECT * FROM NFLInformation ORDER BY NFLInformation.'"+sortingIndicator+"'");
    }

    if(!query.exec()) {
       qDebug() << query.lastError();
    }

    return query;
}

QSqlQuery Database::getSouvenirs(QString souvenirIndicator) {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLSouvenirs WHERE Stadium ='"+souvenirIndicator+"'");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QVector<QString> Database::getTeamsTour() {
    QSqlQuery query(*this);

    QVector<QString> nflTeams;

    query.prepare("SELECT * FROM NFLInformation");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }

    while(query.next()) {
        nflTeams.push_back(query.value(0).toString());
    }
    return nflTeams;
}

QSqlQuery Database::getAllDistances() {
    QSqlQuery query(*this);

//    query.prepare("SELECT * FROM NFLDistances WHERE Beginning = '" + name + "'");
    query.prepare("SELECT * FROM NFLDistances");

    if(!query.exec()) {
        qDebug() << query.lastError();
    }

    return query;
}



