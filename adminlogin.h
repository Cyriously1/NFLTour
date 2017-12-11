#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QWidget>
#include "admin.h"
#include "mainwindow.h"

/**
 * @brief The adminUser struct for admin login
 */
struct adminUser{

    QString username;
    QString password;
};

namespace Ui {
class AdminLogin;
}

/**
 * @brief The AdminLogin class allows the user to log in to the admin window
 */
class AdminLogin : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief AdminLogin
     * @param parent
     */
    explicit AdminLogin(QWidget *parent = 0);
    ~AdminLogin();

    /**
     * @brief isAdmin
     * @param nameIn
     * @param passIn
     * @return
     */
    bool isAdmin(QString nameIn, QString passIn);

private slots:

    /**
     * @brief on_AdminLogin_passwordEdit_returnPressed
     */
    void on_AdminLogin_passwordEdit_returnPressed();

private:
    /**
     * @brief ui
     */
    Ui::AdminLogin *ui;
};

#endif // ADMINLOGIN_H
