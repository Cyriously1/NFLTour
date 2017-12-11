#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QWidget>
#include "admin.h"
#include "mainwindow.h"

struct adminUser{

    QString username;
    QString password;
};

namespace Ui {
class AdminLogin;
}

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
