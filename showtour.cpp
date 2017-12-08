#include "showtour.h"
#include "ui_showtour.h"
#include "database.h"

ShowTour::ShowTour(std::vector<QString> *route, int totalDistance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowTour)
{
    this->route = route;

    ui->setupUi(this);
    this->setFixedSize(this->size());

    // show total distance
    this->ui->label_distance->setText("Distance: " + QString::number(totalDistance) + " mi.");

    // set inital stadium
    ui->label_stadiumName->setText(route->at(0));

    showSouvenirs();
}

ShowTour::~ShowTour()
{
    delete ui;
}

void ShowTour::showSouvenirs() {
    QSqlQuery query = Database::getInstance()->getSouvenirs(route->at(this->currentIndex));

    while(query.next()) {
        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        QLabel *souvenir = new QLabel(query.value(2).toString() + "  ( $" + query.value(3).toString() + " )");
        QLineEdit *quantity = new QLineEdit();

        this->hLayouts.push_back(horizontalLayout);
        this->souvenirLabels.push_back(souvenir);
        this->souvenirQuantityWidgets.push_back(quantity);

        quantity->setFixedWidth(50);
        quantity->setFixedHeight(50);

        horizontalLayout->addWidget(souvenir);
        horizontalLayout->addWidget(quantity);

        souvenir->setStyleSheet("font: 12pt; margin: 8px");
        quantity->setStyleSheet("font: 12pt; margin: 8px");

        ui->verticalLayout->addLayout(horizontalLayout);
    }
}

void ShowTour::showTeam() {
    ui->label_stadiumName->setText(route->at(this->currentIndex));
}

void ShowTour::deleteSouvenirs() {
    if(this->souvenirLabels.empty()) return;

    for(uint i = 0; i < souvenirLabels.size(); ++i) {
        delete souvenirLabels[i];
        delete souvenirQuantityWidgets[i];

        ui->verticalLayout->removeItem(hLayouts[i]);
        delete hLayouts[i];
    }

    // clear vecs
    souvenirLabels.clear();
    souvenirQuantityWidgets.clear();
    hLayouts.clear();
}

void ShowTour::on_pushButton_next_clicked()
{
    this->currentIndex++;
    if(this->currentIndex < route->size()) {
        deleteSouvenirs();
        showTeam();
        showSouvenirs();

    }
}







