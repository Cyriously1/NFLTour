#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "database.h"
#include "sqlquerymodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    SqlQueryModel *nflInfoModel = new SqlQueryModel(0);
    nflInfoModel->setQuery(Database::getInstance()->getTeamInfo());

    SqlQueryModel *stadiumsModel = new SqlQueryModel(0);
    stadiumsModel->setQuery(Database::getInstance()->getAllStadiums());

    SqlQueryModel *openStadiumsModel = new SqlQueryModel(0);
    openStadiumsModel->setQuery(Database::getInstance()->getOpenStadiums());

    SqlQueryModel *seatingCapModel = new SqlQueryModel(0);
    seatingCapModel->setQuery(Database::getInstance()->getStadiumsBySeatingCapacity());

    SqlQueryModel *starPlayersModel = new SqlQueryModel(0);
    starPlayersModel->setQuery(Database::getInstance()->getTeamInfo());

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("nflInfoModel", nflInfoModel);
    engine.rootContext()->setContextProperty("stadiumsModel", stadiumsModel);
    engine.rootContext()->setContextProperty("openStadiumsModel", openStadiumsModel);
    engine.rootContext()->setContextProperty("seatingCapModel", seatingCapModel);
    engine.rootContext()->setContextProperty("starPlayersModel", starPlayersModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
