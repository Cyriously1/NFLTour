#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <QQuickItem>

#include "database.h"
#include "sqlquerymodel.h"
#include "slotobject.h"
#include "sortfilterproxymodel.h"
#include "sqltablemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    app.setWindowIcon(QIcon("Pics/NFLicon.png"));

    qmlRegisterType<SortFilterProxyModel>("SortFilterProxyModel", 0, 1, "SortFilterProxyModel");

    SqlQueryModel *nflInfoModel = new SqlQueryModel(0);
    nflInfoModel->setQuery(Database::getInstance()->getTeamInfo());

    SqlQueryModel *stadiumsModel = new SqlQueryModel(0);
    stadiumsModel->setQuery(Database::getInstance()->getAllStadiums());

    SqlQueryModel *openStadiumsModel = new SqlQueryModel(0);
    openStadiumsModel->setQuery(Database::getInstance()->getOpenStadiums());

    SqlQueryModel *seatingCapModel = new SqlQueryModel(0);
    seatingCapModel->setQuery(Database::getInstance()->getStadiumsBySeatingCapacity().query);

    SqlQueryModel *starPlayersModel = new SqlQueryModel(0);
    starPlayersModel->setQuery(Database::getInstance()->getTeamInfo());

    SqlQueryModel *afcInfoModel = new SqlQueryModel(0);
    afcInfoModel->setQuery(Database::getInstance()->getAFC());

    SqlQueryModel *nfcInfoModel = new SqlQueryModel(0);
    nfcInfoModel->setQuery(Database::getInstance()->getNFC());

    SqlQueryModel *souvenirModel = new SqlQueryModel(0);
    souvenirModel->setQuery(Database::getInstance()->getSouvenirs());

    SqlTableModel *adminModel = new SqlTableModel();
    adminModel->setTable("NFLInformation");
//    adminModel->applyRoles();
    adminModel->select();




    QQmlApplicationEngine engine;
    SlotObject *slotObj = new SlotObject;

    engine.rootContext()->setContextProperty("nflInfoModel", nflInfoModel);
    engine.rootContext()->setContextProperty("stadiumsModel", stadiumsModel);
    engine.rootContext()->setContextProperty("openStadiumsModel", openStadiumsModel);
    engine.rootContext()->setContextProperty("seatingCapModel", seatingCapModel);
    engine.rootContext()->setContextProperty("starPlayersModel", starPlayersModel);
    engine.rootContext()->setContextProperty("afcInfoModel", afcInfoModel);
    engine.rootContext()->setContextProperty("nfcInfoModel", nfcInfoModel);
    engine.rootContext()->setContextProperty("souvenirModel", souvenirModel);
    engine.rootContext()->setContextProperty("adminModel", adminModel);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QList<QObject*> list = engine.rootObjects();
    QObject *textin = list[0]->findChild<QObject*>("qmlText");

    QLocale english(QLocale::English);
//    qDebug() << Database::getInstance()->getStadiumsBySeatingCapacity().total;
//    qDebug() << list[0]->findChild<QObject*>("qmlCapacity");
    QObject *labelIn = list[0]->findChild<QObject*>("qmlCapacity");
    labelIn->setProperty("text", QVariant("Total Seating Capacity: " + english.toString(Database::getInstance()->getStadiumsBySeatingCapacity().total)));

    QObject::connect(textin, SIGNAL(qmlSignal(QString)),
                     slotObj, SLOT(cppSlot(QString)));


//    QList<QObject*> list = engine.rootObjects();

//    QObject *textin = list[0]->findChild<QObject*>("qmlText");
//    QString input = textin->property("text").toString();
//    qDebug() << "from QML: " << input;

//    searchTeam->setQuery(Database::getInstance()->getSearchTeam(input));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
