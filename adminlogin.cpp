#include "adminlogin.h"
#include "ui_adminlogin.h"
#include <QDebug>

AdminLogin::AdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);
}

AdminLogin::~AdminLogin()
{
    delete ui;
}

void AdminLogin::on_AdminLogin_loginButton_clicked()
{
    QString inName = ui->AdminLogin_usernameEdit->text();
    QString inPass = ui->AdminLogin_passwordEdit->text();

    qDebug() << inName;
    qDebug() << inPass;

    if(isAdmin(inName,inPass))
    {
        admin *adminPage = new admin();
        this->close();
        adminPage->exec();
    }
}

bool AdminLogin::isAdmin(QString nameIn, QString passIn)
{
    bool isAdmin = false;
    if(nameIn == "Fake" && passIn == "Team")
    {
        isAdmin = true;
    }
    return isAdmin;
}
