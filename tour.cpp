#include "tour.h"
#include "ui_tour.h"

Tour::Tour(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tour)
{
    ui->setupUi(this);
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
