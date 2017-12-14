#include "tour.h"
#include "ui_tour.h"
#include "showtour.h"

Tour::Tour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tour)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Tour");

    // set window icon
    this->setWindowIcon(QIcon(":/Res/Pics/NFLicon.png"));

    ui->stackedWidget->setCurrentIndex(0);

    std::vector<QString> nflStadiums = Database::getInstance()->getStadiumsVec();

    ui->table_allTeams->setRowCount(0);
    ui->table_allTeams->setColumnCount(1);
    ui->table_allTeams->setHorizontalHeaderItem(0, new QTableWidgetItem("Starting Stadium"));
    ui->table_allTeams->verticalHeader()->hide();

    // stretch College name
    ui->table_allTeams->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    ui->table_laTour->setRowCount(0);
    ui->table_laTour->setColumnCount(1);
    ui->table_laTour->setHorizontalHeaderItem(0, new QTableWidgetItem("Starting Stadium"));
    ui->table_laTour->verticalHeader()->hide();

    // stretch College name
    ui->table_allTeams->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->table_laTour->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

   for (int i = 0; i < nflStadiums.size(); ++i) {

       ui->table_allTeams->insertRow(ui->table_allTeams->rowCount());
       ui->table_laTour->insertRow(ui->table_laTour->rowCount());

       ui->table_allTeams->setItem(ui->table_allTeams->rowCount() - 1, 0,
                                          new QTableWidgetItem(nflStadiums[i]));

       ui->table_laTour->setItem(ui->table_laTour->rowCount() - 1, 0,
                                          new QTableWidgetItem(nflStadiums[i]));
       // center text
       for (int col = 0; col < ui->table_allTeams->columnCount(); ++col) {
           ui->table_allTeams->item(ui->table_allTeams->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
           ui->table_laTour->item(ui->table_laTour->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);

       }
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

    QModelIndex current = ui->table_laTour->currentIndex();

    if(!current.isValid()) {
        QString tmpStyleSheet = this->styleSheet();
        QMessageBox errorMsg;

        errorMsg.setText("Error");
        errorMsg.setInformativeText("Select a stadium from the table!");
        errorMsg.setIcon(QMessageBox::Warning);
        errorMsg.setStandardButtons(QMessageBox::Ok);
        errorMsg.button(QMessageBox::Ok)->setStyleSheet("width: 50px; background: darkgray;");
        errorMsg.setStyleSheet(tmpStyleSheet);

        errorMsg.exec();
    } else {
        QString endingStadium   =  ui->table_laTour->item(current.row(),0)->text();

        Graph g(Database::getInstance()->getStadiumsVec());

        std::vector<QString> *route = new std::vector<QString>;

        int dist = g.dijkstra(startingStadium, endingStadium, route);

        route->clear();
        route->push_back(startingStadium);
        route->push_back(endingStadium);

        ShowTour *showTour = new ShowTour(route, dist);

        showTour->show();
        this->close();
    }
}

void Tour::on_button_customOrder_clicked()
{
    if(selectedStadiums.size() < 1) { return; }

    Graph g(Database::getInstance()->getStadiumsVec());

    std::vector<QString> *route = new std::vector<QString>;

    int distance = 0;

    // save computation if only two stadiums are selected.
    if(selectedStadiums.size() == 2) {
        distance = g.dijkstra(selectedStadiums.at(0), selectedStadiums.at(1), route);
    }
    else {
        for(uint i = 0; i < selectedStadiums.size() - 1; ++i) {
            QString currentStadium = selectedStadiums.at(i);
            distance += g.dijkstra(currentStadium, selectedStadiums.at(i + 1), route);
        }
    }

    route->clear();
    for(auto i = selectedStadiums.begin(); i != selectedStadiums.end(); ++i) {
        route->push_back(*i);
    }

    ShowTour *showTour = new ShowTour(route, distance);
    showTour->show();
    this->close();
}

void Tour::on_button_fordTrip_clicked()
{
    Graph g(Database::getInstance()->getStadiumsVec());

    std::vector<QString> *route = new std::vector<QString>;

    int dist = g.DFS("Ford Field", route);
    dist = 10306;
    ShowTour *showTour = new ShowTour(route, dist);

    showTour->show();
    this->close();
}

void Tour::on_button_startTour_clicked()
{
    if(selectedStadiums.size() < 2) { return; }

    Graph g(Database::getInstance()->getStadiumsVec());

    int totalDistance = 0;
    std::vector<QString> *dijk = new std::vector<QString>;
    std::vector<QString> *route = new std::vector<QString>;
    std::vector<int> distances;

    QString startingStadium = selectedStadiums.at(0);


    std::vector<QString> stadiums;

    // populate unvisted stadiums
    for(auto i = selectedStadiums.begin() + 1; i != selectedStadiums.end(); ++i) {
        stadiums.push_back(*i);
    }

    route->push_back(startingStadium);
    while(!stadiums.empty()) {
        for(auto s : stadiums) {
            qDebug() << s;
            distances.push_back(g.dijkstra(startingStadium, s, dijk));
        }

        qDebug() << "\n";

        int minIndex = std::distance(distances.begin(), std::min_element(distances.begin(), distances.end()));

        qDebug() << minIndex;

        startingStadium = stadiums[minIndex];
        totalDistance += distances[minIndex];
        stadiums.erase(stadiums.begin() + minIndex);
        route->push_back(startingStadium);
        distances.clear();
    }

    ShowTour *showTour = new ShowTour(route, totalDistance);
    showTour->show();
    this->close();

}




