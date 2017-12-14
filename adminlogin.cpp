#include "adminlogin.h"
#include "ui_adminlogin.h"
#include <QDebug>

AdminLogin::AdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Administrator Login");

    // set window icon
    this->setWindowIcon(QIcon(":/Res/Pics/NFLicon.png"));
}


AdminLogin::~AdminLogin()
{
    delete ui;
}


bool AdminLogin::isAdmin(QString nameIn, QString passIn)
{
    bool isAdmin = false;
    if(nameIn == "a" && passIn == "a")
    {
        isAdmin = true;
    }
    return isAdmin;
}


void AdminLogin::on_AdminLogin_passwordEdit_returnPressed()
{
    QString inName = ui->AdminLogin_usernameEdit->text();
    QString inPass = ui->AdminLogin_passwordEdit->text();

    if(isAdmin(inName,inPass))
    {
        admin *adminPage = new admin();
        this->close();
        adminPage->exec();
    }
}
