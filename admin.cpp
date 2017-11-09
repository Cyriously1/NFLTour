#include "admin.h"
#include "ui_admin.h"

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    // Team Info table setup
    ui->tableWidget_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_table->setColumnCount(8);
    QStringList teamInfoTableHeaders;
    teamInfoTableHeaders << "Team Name" << "Stadium Name" << "Seating Capacity" << "Location"
                         << "Conference" << "Surface Type" << "Roof Type" << "Start Player";
    ui->tableWidget_table->setHorizontalHeaderLabels(teamInfoTableHeaders);

}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_back_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void admin::on_pushButton_showTable_clicked()
{
    QSqlQuery query = Database::getInstance()->getTeamInfo();

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
        ui->tableWidget_table->insertRow(ui->tableWidget_table->rowCount());

        // insert items
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 0, teamName);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 1, stadiumName);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 2, seatingCap);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 3, location);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 4, conference);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 5, surfaceType);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 6, roofType);
        ui->tableWidget_table->setItem(ui->tableWidget_table->rowCount() - 1, 7, starPlayer);
    }

}
