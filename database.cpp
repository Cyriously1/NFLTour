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

QSqlQuery Database::getAFC() {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE Conference = 'American Football Conference' ORDER BY NFLInformation.TeamName ASC");


    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

QSqlQuery Database::getNFC() {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE Conference = 'National Football Conference' ORDER BY NFLInformation.TeamName ASC");


    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}

void Database::addSailors(QString input)
{
    QString teamName;
    QString stadium;
    QString capacity;
    QString location;
    QString conference;
    QString surfaceType;
    QString roofType;
    QString starPlayer;

    QString fileName = input;
    fileName.remove(0,8);

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       teamName = in.readLine();
       stadium = in.readLine();
       capacity = in.readLine();
       location = in.readLine();
       conference = in.readLine();
       surfaceType = in.readLine();
       roofType = in.readLine();
       starPlayer = in.readLine();
       inputFile.close();
    }

//    qDebug() << fileName;
//    qDebug() << teamName;
//    qDebug() << stadium;
//    qDebug() << capacity;
//    qDebug() << location;
//    qDebug() << conference;
//    qDebug() << surfaceType;
//    qDebug() << roofType;
//    qDebug() << starPlayer;

    QSqlQuery query(*this);

    query.prepare("INSERT INTO NFLInformation (TeamName, StadiumName, SeatingCapacity, Location, Conference, SurfaceType, StadiumRoofType, StarPlayer) "
                  "VALUES (:teamName, :stadium, :capacity, :location, :conference, :surfaceType, :roofType, :starPlayer)");
    query.bindValue(":teamName", teamName);
    query.bindValue(":stadium", stadium);
    query.bindValue(":capacity", capacity);
    query.bindValue(":location", location);
    query.bindValue(":conference", conference);
    query.bindValue(":surfaceType", surfaceType);
    query.bindValue(":roofType", roofType);
    query.bindValue(":starPlayer", starPlayer);
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

void Database::addSouvenir(QString stadiumName, QString newSouvName, QString newSouvPrice)
{
    double newSouvPriceDbl = newSouvPrice.toDouble();
    QString teamName;

    QSqlQuery query(*this);

    query.prepare("SELECT TeamName FROM NFLSouvenirs WHERE Stadium = :stadiumName");
    query.bindValue(":stadiumName", stadiumName);
    if(!query.exec()) {
        qDebug() << "addSouvenir() query: " << query.lastError();
    }
    while(query.next()) {
        teamName = query.value(0).toString();
    }

    query.prepare("INSERT INTO NFLSouvenirs (TeamName,Stadium,Name,Price) VALUES (:teamName, :stadiumName, :name, :price)");
    query.bindValue(":teamName", teamName);
    query.bindValue(":stadiumName", stadiumName);
    query.bindValue(":name", newSouvName);
    query.bindValue(":price", newSouvPriceDbl);
    if(!query.exec()) {
        qDebug() << "addSouvenir() query: " << query.lastError();
    }
}

void Database::removeSouvenir(QString stadium, QString name)
{
    QSqlQuery query(*this);

    query.prepare("DELETE FROM NFLSouvenirs WHERE Stadium = :stadium AND Name = :name");
    query.bindValue(":stadium", stadium);
    query.bindValue(":name", name);
    if(!query.exec()) {
       qDebug() << query.lastError();
    }

}

int Database::displayOpenStadiums()
{
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLInformation WHERE NFLInformation.StadiumRoofType = 'Open' "
                  "ORDER BY NFLInformation.TeamName ASC");
    if(!query.exec()) {
       qDebug() << query.lastError();
    }

    int counter = 0;
    QLocale english(QLocale::English);
    QVector<QString> stadiumNames;
    while(query.next())
    {
        //Find duplicated stadium names. Returns -1 into i if none found.
        int i = stadiumNames.indexOf(query.value(1).toString());
        stadiumNames.push_back(query.value(1).toString());
        if(i == -1)//if no duplicate is found
        {
            counter++;
        }
    }

    return counter;
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

capTable Database::getStadiumsBySeatingCapacity() {
    QSqlQuery query(*this);
    capTable table;

    query.prepare("SELECT * FROM NFLInformation ORDER BY NFLInformation.SeatingCapacity ASC");

    QSqlQuery copyQuery = query;
    int totalCap = 0;
    QLocale english(QLocale::English);
    copyQuery.exec();
    QVector<QString> stadiumNames;
    while(copyQuery.next())
    {
        int i = stadiumNames.indexOf(copyQuery.value(1).toString());
        stadiumNames.push_back(copyQuery.value(1).toString());

        if(i == -1)
        {
            totalCap += english.toDouble(copyQuery.value(2).toString());
        }
    }

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    table.query = query;
    table.total = totalCap;

    return table;
}

QSqlQuery Database::sortTable(int index) {
    QSqlQuery query(*this);

    QString sortingIndicator = "";

    qDebug() << index;
    switch(index) {
        case 1:
            sortingIndicator = "TeamName";
            break;
        case 2:
            sortingIndicator = "StadiumName";
            //query.prepare("SELECT * FROM NFLInformation ORDER BY NFLInformation.StadiumName");

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
   query.prepare("SELECT * FROM NFLInformation ORDER BY NFLInformation.'"+sortingIndicator+"'");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }

    return query;
}

QSqlQuery Database::getSouvenirs() {
    QSqlQuery query(*this);

    query.prepare("SELECT * FROM NFLSouvenirs ORDER BY NFLSouvenirs.TeamName ASC");

    if(!query.exec()) {
       qDebug() << query.lastError();
    }
    return query;
}



