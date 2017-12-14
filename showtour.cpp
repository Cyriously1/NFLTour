#include "showtour.h"
#include "ui_showtour.h"
#include "database.h"
#include "tour.h"

ShowTour::ShowTour(std::vector<QString> *route, int totalDistance, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowTour)
{
    this->route = route;

    ui->setupUi(this);
    this->setFixedSize(this->size());

    // set window title
    this->setWindowTitle("NFL Show Tour");

    // set window icon
    this->setWindowIcon(QIcon(":/Res/Pics/NFLicon.png"));

    // show total distance
    this->ui->label_distance->setText("Distance: " + QString::number(totalDistance) + " Miles.");

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
        // make map & vec to save souvenirs n thur prices
        souvenirPriceMap[query.value(2).toString()] = query.value(3).toDouble();
        souvenirs.push_back(query.value(2).toString());

        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        QLabel *souvenir = new QLabel(query.value(2).toString() + "  ( $" + QString::number(query.value(3).toDouble(), 'f',2) + " )");
        QLineEdit *quantity = new QLineEdit();

        // prevents the user of inputing any ugly ass letters or commas
        QValidator *validator = new QIntValidator(1, 100, this);
        quantity->setValidator(validator);

        this->hLayouts.push_back(horizontalLayout);
        this->souvenirLabels.push_back(souvenir);
        this->souvenirQuantityWidgets.push_back(quantity);

        quantity->setFixedWidth(50);
        quantity->setFixedHeight(50);

        horizontalLayout->addWidget(souvenir);
        horizontalLayout->addWidget(quantity);

        souvenir->setStyleSheet("font: 12pt; margin: 8px");
        quantity->setStyleSheet("font: 12pt; margin: 8px; background: lightgray; color: black; font-weight: bold; "
                                "font: helvatica;");

        ui->verticalLayout->addLayout(horizontalLayout);
    }
}

void ShowTour::showTeam() {
    ui->label_stadiumName->setText(route->at(this->currentIndex));
}

void ShowTour::deleteSouvenirs() {
    if(this->souvenirLabels.empty()) return;

    souvenirPriceMap.clear();
    souvenirs.clear();

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


void ShowTour::calculateCost() {
    double cost = 0;
    for(uint i = 0; i < souvenirQuantityWidgets.size(); ++i) {
        QString txt = souvenirQuantityWidgets[i]->text();

        bool ok;
        int qt = txt.toInt(&ok);

        if(ok) {
            cost += souvenirPriceMap[souvenirs[i]] * qt;
        }
    }
    reciept[route->at(currentIndex)] = cost;

    totalCost += cost;
    ui->label_cost->setText("Cost: $ " + QString::number(totalCost, 'f', 2));
}

void ShowTour::on_pushButton_next_clicked()
{
    if(this->currentIndex < route->size())
        calculateCost();

    this->currentIndex++;
    if(this->currentIndex < route->size()) {
        deleteSouvenirs();
        showTeam();
        showSouvenirs();

    } else {
        showReciept();
    }
}

void ShowTour::on_pushButton_previous_clicked()
{
    this->currentIndex--;
    if(this->currentIndex >= 0) {
        deleteSouvenirs();
        showTeam();
        showSouvenirs();

    }

}

void ShowTour::showReciept() {
    deleteSouvenirs();

    ui->label_stadiumName->setText("Tour Finished");
    ui->label_souvenirs->setText("Reciept");
    ui->pushButton_next->hide();
    ui->pushButton_previous->hide();


    for(auto i = reciept.begin(); i != reciept.end(); ++i) {

        QHBoxLayout *horizontalLayout = new QHBoxLayout();
        QLabel *recieptItem = new QLabel(i->first + "  ( $ " + QString::number(i->second, 'f', 2) + " )");

        this->hLayouts.push_back(horizontalLayout);
        this->souvenirLabels.push_back(recieptItem);

        horizontalLayout->addWidget(recieptItem);

        recieptItem->setStyleSheet("font: 12pt; margin: 8px");

        ui->verticalLayout->addLayout(horizontalLayout);
    }
}

void ShowTour::on_pushButton_back_clicked()
{
    Tour *tp = new Tour();

    tp->show();
    this->close();

}
