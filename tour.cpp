#include "tour.h"
#include "ui_tour.h"

Tour::Tour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tour)
{
    ui->setupUi(this);

    QVector<QString> nflTeams = Database::getInstance()->getTeamsTour();

    ui->table_allTeams->setRowCount(0);
    ui->table_allTeams->setColumnCount(1);
    ui->table_allTeams->setHorizontalHeaderItem(0, new QTableWidgetItem("Starting Stadium"));
    ui->table_allTeams->verticalHeader()->hide();

    // stretch College name
    ui->table_allTeams->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

   for (int i = 0; i < nflTeams.size(); ++i) {

       ui->table_allTeams->insertRow(ui->table_allTeams->rowCount());

       ui->table_allTeams->setItem(ui->table_allTeams->rowCount() - 1, 0,
                                          new QTableWidgetItem(nflTeams[i]));

       // center text
       for (int col = 0; col < ui->table_allTeams->columnCount(); ++col) {
           ui->table_allTeams->item(ui->table_allTeams->rowCount() - 1, col)->setTextAlignment(Qt::AlignCenter);
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


/**
 * @brief tourCampuses::displaySelectedColleges
 */
void Tour::displaySelectedColleges()
{

    ui->table_selectedTeams->setRowCount(0);
    ui->table_selectedTeams->setColumnCount(1);
    ui->table_selectedTeams->setHorizontalHeaderItem(0, new QTableWidgetItem("Selected Stadiums"));
    ui->table_selectedTeams->verticalHeader()->hide();
    ui->table_selectedTeams->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    for (int i = 0; i < selectedColleges.size(); ++i) {
        ui->table_selectedTeams->insertRow(ui->table_selectedTeams->rowCount());

        ui->table_selectedTeams->setItem(ui->table_selectedTeams->rowCount() - 1, 0,
                                           new QTableWidgetItem(selectedColleges.at(i)));

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
        selectedColleges.push_back(ui->table_allTeams->item(current.row(),0)->text());

    displaySelectedColleges();
    }
}

void Tour::on_pushButton_delete_clicked()
{
    if(selectedColleges.empty()) {
        QMessageBox::warning(this, "Error", "There is no college selected!");
    } else {
        selectedColleges.pop_back();
        displaySelectedColleges();
    }
}
