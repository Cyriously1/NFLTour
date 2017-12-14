#include "adminextraspopup.h"
#include "ui_adminextraspopup.h"
#include <vector>
#include <QDebug>


AdminExtrasPopup::AdminExtrasPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminExtrasPopup)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Admin Extras");

    // set window icon
    this->setWindowIcon(QIcon(":/Res/Pics/NFLicon.png"));

    g = new Graph(Database::getInstance()->getStadiumsVec());

    // table setup
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


AdminExtrasPopup::~AdminExtrasPopup()
{
    delete ui;
}


void AdminExtrasPopup::on_pushButton_back_clicked()
{
    admin *a = new admin();

    a->show();
    this->close();
}


void AdminExtrasPopup::on_MST_clicked()
{
    std::vector< Graph::intPair > *mst = new std::vector< Graph::intPair >;
    int dist = g->MST(mst);

    //make table
    ui->tableWidget->setColumnCount(2);
    QStringList headers;
    headers << "From" << "To";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(0);


    for(auto pair : *mst) {
        QTableWidgetItem *from = new QTableWidgetItem(g->stadiums[pair.first]);
        QTableWidgetItem *to = new QTableWidgetItem(g->stadiums[pair.second]);

        from->setTextAlignment(Qt::AlignCenter);
        to->setTextAlignment(Qt::AlignCenter);

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());

        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, from);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, to);

    }

    // set distance
    ui->label_distance->setText("Distance: " + QString::number(dist) + " miles");

    ui->lineEdit->clear();
}


void AdminExtrasPopup::on_DFS_clicked()
{
    QString stadium = ui->lineEdit->text();

    std::vector<QString> stadiums = Database::getInstance()->getStadiumsVec();

    // if valid stadium
    if(std::find(stadiums.begin(), stadiums.end(), stadium) != stadiums.end()) {
        std::vector<QString> *route = new std::vector<QString>;
        int dist = g->DFS(stadium, route);

        //make table
        ui->tableWidget->setColumnCount(1);
        QStringList headers;
        headers << "Stadium";
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setRowCount(0);

        for(auto s : *route) {
            QTableWidgetItem *stad = new QTableWidgetItem(s);

            stad->setTextAlignment(Qt::AlignCenter);

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, stad);
        }

        ui->label_distance->setText("Distance: " + QString::number(dist) + " miles");

    } else {
        ui->lineEdit->clear();
    }
}


void AdminExtrasPopup::on_BFS_clicked()
{
    QString stadium = ui->lineEdit->text();

    std::vector<QString> stadiums = Database::getInstance()->getStadiumsVec();

    // if valid stadium
    if(std::find(stadiums.begin(), stadiums.end(), stadium) != stadiums.end()) {
        std::vector<QString> *route = new std::vector<QString>;
        int dist = g->BFS(stadium, route);

        //make table
        ui->tableWidget->setColumnCount(1);
        QStringList headers;
        headers << "Stadium";
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setRowCount(0);

        for(auto s : *route) {
            QTableWidgetItem *stad = new QTableWidgetItem(s);

            stad->setTextAlignment(Qt::AlignCenter);

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, stad);
        }

        ui->label_distance->setText("Distance: " + QString::number(dist) + " miles");

    } else {
        ui->lineEdit->clear();
    }
}
