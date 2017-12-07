#include "tour.h"
#include "ui_tour.h"

Tour::Tour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tour)
{
    ui->setupUi(this);

    std::vector<QString> nflStadiums = Database::getInstance()->getStadiumsVec();

    ui->table_allTeams->setRowCount(0);
    ui->table_allTeams->setColumnCount(1);
    ui->table_allTeams->setHorizontalHeaderItem(0, new QTableWidgetItem("Starting Stadium"));
    ui->table_allTeams->verticalHeader()->hide();

    // stretch College name
    ui->table_allTeams->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

   for (int i = 0; i < nflStadiums.size(); ++i) {

       ui->table_allTeams->insertRow(ui->table_allTeams->rowCount());

       ui->table_allTeams->setItem(ui->table_allTeams->rowCount() - 1, 0,
                                          new QTableWidgetItem(nflStadiums[i]));

       // center text
       for (int col = 0; col < ui->table_allTeams->columnCount(); ++col) {
           ui->table_allTeams->item(ui->table_allTeams->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
       }

       ui->comboBox_stadiums->addItem(nflStadiums.at(i));
   }
}

Tour::~Tour()
{
    delete ui;
}

void Tour::on_pushButton_back_clicked()
{
    MainWindow *window = new MainWindow();
    window->show();
    this->close();
}


/**
 * @brief tourCampuses::displayselectedStadiums
 */
void Tour::displayselectedStadiums()
{

    ui->table_selectedTeams->setRowCount(0);
    ui->table_selectedTeams->setColumnCount(1);
    ui->table_selectedTeams->setHorizontalHeaderItem(0, new QTableWidgetItem("Selected Stadiums"));
    ui->table_selectedTeams->verticalHeader()->hide();
    ui->table_selectedTeams->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    for (int i = 0; i < selectedStadiums.size(); ++i) {
        ui->table_selectedTeams->insertRow(ui->table_selectedTeams->rowCount());

        ui->table_selectedTeams->setItem(ui->table_selectedTeams->rowCount() - 1, 0,
                                           new QTableWidgetItem(selectedStadiums.at(i)));

        // center text
        for (int col = 0; col < ui->table_selectedTeams->columnCount(); ++col) {
            ui->table_selectedTeams->item(ui->table_selectedTeams-> rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);

        }
    }
}

void Tour::on_pushButton_add_clicked()
{
    QModelIndex current = ui->table_allTeams->currentIndex();

    if(!current.isValid()) {
        QMessageBox::warning(this, "Error", "Select A College from the table!");
    } else {
        selectedStadiums.push_back(ui->table_allTeams->item(current.row(),0)->text());

    displayselectedStadiums();
    }
}

void Tour::on_pushButton_delete_clicked()
{
    if(selectedStadiums.empty()) {
        QMessageBox::warning(this, "Error", "There is no college selected!");
    } else {
        selectedStadiums.pop_back();
        displayselectedStadiums();
    }
}

void Tour::on_button_startTour_clicked()
{
    std::vector<QString> *route;

    Graph g(selectedStadiums);

    int distance = g.dijkstra(selectedStadiums.at(0), selectedStadiums.at(selectedStadiums.size() - 1), route);


    qDebug() << "***********HERE ******************";
    qDebug() << distance;

    for(int index = 0; index < route->size(); index++) {

        qDebug() << route->at(index) << " ";
    }

}

void Tour::on_button_laTrip_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Tour::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Tour::on_button_laStartTour_clicked()
{
    QString startingStadium = "Los Angeles Memorial Coliseum";
    QString endingStadium   = ui->comboBox_stadiums->currentText();

    Graph g(Database::getInstance()->getStadiumsVec());

    std::vector<QString> *route = new std::vector<QString>;

    int dist = g.dijkstra(startingStadium, endingStadium, route);

    qDebug() << dist;

    for(int index = 0; index < route->size(); index++) {
        qDebug() << route->at(index);
    }
}

























