#include "tour.h"
#include "ui_tour.h"

Tour::Tour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tour)
{
    ui->setupUi(this);

    QVector<QString> nflTeams = Database::getInstance()->getTeamsTour();

    for(int index = 0; index < nflTeams.length(); index++) {
        qDebug() << nflTeams.at(index);
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




