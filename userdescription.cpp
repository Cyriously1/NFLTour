#include "userdescription.h"
#include "ui_userdescription.h"

UserDescription::UserDescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDescription)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Tour Description");

    // set window icon
    this->setWindowIcon(QIcon(":/Res/Pics/NFLicon.png"));
}

UserDescription::~UserDescription()
{
    delete ui;
}

void UserDescription::on_button_back_clicked()
{
    MainWindow *window = new MainWindow();
    window->show();
    this->close();
}
