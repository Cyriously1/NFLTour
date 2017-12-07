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

void Database::addSailors()
{
    QSqlQuery query(*this);

    query.prepare("INSERT INTO NFLInformation (TeamName, StadiumName, SeatingCapacity, Location, Conference, SurfaceType, StadiumRoofType, StarPlayer) VALUES ('San Diego Sailors','Qualcomm Stadium','71,500','San Diego, California','American Football Conference','Bandera Bermuda Grass','Open','Kenny Rogers')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLSouvenirs (TeamName, Stadium, Name, Price) VALUES ('San Diego Sailors','Qualcomm Stadium','Signed Helmet','71.99')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLSouvenirs (TeamName, Stadium, Name, Price) VALUES ('San Diego Sailors','Qualcomm Stadium','Autographed Football','79.39')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLSouvenirs (TeamName, Stadium, Name, Price) VALUES ('San Diego Sailors','Qualcomm Stadium','Team Pennant','17.99')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLSouvenirs (TeamName, Stadium, Name, Price) VALUES ('San Diego Sailors','Qualcomm Stadium','Team Picture','19.99')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLSouvenirs (TeamName, Stadium, Name, Price) VALUES ('San Diego Sailors','Qualcomm Stadium','Team Jersey','199.99')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLDistances (Beginning, Ending, Distance) VALUES ('Qualcomm Stadium','University of Phoenix Stadium','300')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLDistances (Beginning, Ending, Distance) VALUES ('Qualcomm Stadium','Los Angeles Memorial Coliseum','121')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLDistances (Beginning, Ending, Distance) VALUES ('Qualcomm Stadium','Sports Authority Field at Mile High','830')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLDistances (Beginning, Ending, Distance) VALUES ('University of Phoenix Stadium','Qualcomm Stadium','300')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLDistances (Beginning, Ending, Distance) VALUES ('Los Angeles Memorial Coliseum','Qualcomm Stadium','121')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();

    query.prepare("INSERT INTO NFLDistances (Beginning, Ending, Distance) VALUES ('Sports Authority Field at Mile High','Qualcomm Stadium','830')");
    if(!query.exec()) {
        qDebug() << "addSailors() query: " << query.lastError();
    }
    query.clear();
}

void Database::moveRams()
{
    QSqlQuery query(*this);

    query.prepare("UPDATE NFLInformation SET StadiumName = 'Farmers Field'  WHERE TeamName = 'Los Angeles Rams'");
    if(!query.exec()) {
        qDebug() << "moveRams() query: " << query.lastError();
    }
    query.clear();

    query.prepare("UPDATE NFLSouvenirs SET Stadium = 'Farmers Field'  WHERE TeamName = 'Los Angeles Rams'");
    if(!query.exec()) {
        qDebug() << "moveRams() query: " << query.lastError();
    }
    query.clear();

    query.prepare("UPDATE NFLDistances SET Beginning = 'Farmers Field'  WHERE Beginning = 'Los Angeles Memorial Coliseum'");
    if(!query.exec()) {
        qDebug() << "moveRams() query: " << query.lastError();
    }
    query.clear();

    query.prepare("UPDATE NFLDistances SET Ending = 'Farmers Field'  WHERE Ending = 'Los Angeles Memorial Coliseum'");
    if(!query.exec()) {
        qDebug() << "moveRams() query: " << query.lastError();
    }
    query.clear();
}

std::vector<QString> Database::getStadiumsVec() {
    QSqlQuery query(*this);

    std::vector<QString> stadiums;

    query.prepare("SELECT * FROM NFLInformation");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }

    while(query.next()) {
        stadiums.push_back(query.value(1).toString());
    }
    return stadiums;
}



