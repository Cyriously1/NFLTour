#include "adminlogin.h"
#include "ui_adminlogin.h"
#include <QDebug>

/**
 * @brief AdminLogin::AdminLogin
 * @param parent
 */
AdminLogin::AdminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminLogin)
{
    ui->setupUi(this);

    // set window title
    this->setWindowTitle("NFL Administrator Login");

    // set window icon
    this->setWindowIcon(QIcon("Pics/NFLicon.png"));
}

/**
 * @brief AdminLogin::~AdminLogin
 */
AdminLogin::~AdminLogin()
{
    delete ui;
}

/**
 * @brief AdminLogin::isAdmin
 * @param nameIn
 * @param passIn
 * @return
 */
bool AdminLogin::isAdmin(QString nameIn, QString passIn)
{
    bool isAdmin = false;
    if(nameIn == "a" && passIn == "a")
    {
        isAdmin = true;
    }
    return isAdmin;
}

/**
 * @brief AdminLogin::on_AdminLogin_passwordEdit_returnPressed
 */
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
