#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Tour");

    // remove ugly ass toolbar
    this->removeToolBar(this->ui->mainToolBar);

    // Team Info table setup
    ui->teamInfo_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamInfo_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->teamInfo_table->setColumnCount(8);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name" << "Seating Capacity" << "Location"
                         << "Conference" << "Surface Type" << "Roof Type" << "Start Player";
    ui->teamInfo_table->setHorizontalHeaderLabels(teamInfoTableHeaders);

    ui->comboBox_nflType->addItem("All NFL Teams");
    ui->comboBox_nflType->addItem("AFC");
    ui->comboBox_nflType->addItem("NFC");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayTable(QSqlQuery query) {

    // loop through every record in the query
    while(query.next()) {
        QTableWidgetItem *teamName = new QTableWidgetItem(query.value(0).toString());
        QTableWidgetItem *stadiumName = new QTableWidgetItem(query.value(1).toString());
        QTableWidgetItem *seatingCap = new QTableWidgetItem(query.value(2).toString());
        QTableWidgetItem *location = new QTableWidgetItem(query.value(3).toString());
        QTableWidgetItem *conference = new QTableWidgetItem(query.value(4).toString());
        QTableWidgetItem *surfaceType = new QTableWidgetItem(query.value(5).toString());
        QTableWidgetItem *roofType = new QTableWidgetItem(query.value(6).toString());
        QTableWidgetItem *starPlayer = new QTableWidgetItem(query.value(7).toString());

        // center items
        teamName->setTextAlignment(Qt::AlignCenter);
        stadiumName->setTextAlignment(Qt::AlignCenter);
        seatingCap->setTextAlignment(Qt::AlignCenter);
        location->setTextAlignment(Qt::AlignCenter);
        conference->setTextAlignment(Qt::AlignCenter);
        surfaceType ->setTextAlignment(Qt::AlignCenter);
        roofType->setTextAlignment(Qt::AlignCenter);
        starPlayer ->setTextAlignment(Qt::AlignCenter);

        // insert new row
        ui->teamInfo_table->insertRow(ui->teamInfo_table->rowCount());

        // insert items
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 0, teamName);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 1, stadiumName);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 2, seatingCap);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 3, location);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 4, conference);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 5, surfaceType);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 6, roofType);
        ui->teamInfo_table->setItem(ui->teamInfo_table->rowCount() - 1, 7, starPlayer);

    }
}

void MainWindow::on_lineEdit_searchNflTeams_textEdited(const QString &arg1)
{
    QSqlQuery query = Database::getInstance()->getTeamInfo();

    ui->teamInfo_table->setRowCount(0);

    query.exec("SELECT * FROM TeamInfo WHERE LOWER([Team Name]) LIKE '%"+arg1.toLower()+"%'");
    displayTable(query);
}

void MainWindow::on_comboBox_nflType_currentIndexChanged(int index)
{
    // clear rows
    ui->teamInfo_table->setRowCount(0);
    QSqlQuery query = Database::getInstance()->getTeamInfo();

    switch (index)
    {
    case 0:
        displayTable(query);
        break;
    case 1:
        query.exec("SELECT * FROM TeamInfo WHERE Conference = 'American Football Conference'");
        displayTable(query);
        break;
    case 2:
        query.exec("SELECT * FROM TeamInfo WHERE Conference = 'National Football Conference'");
        displayTable(query);
        break;
    }
}
