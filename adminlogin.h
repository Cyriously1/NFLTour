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
    explicit AdminLogin(QWidget *parent = 0);
    ~AdminLogin();

    bool isAdmin(QString nameIn, QString passIn);

private slots:

    void on_AdminLogin_passwordEdit_returnPressed();

private:
    Ui::AdminLogin *ui;
};

#endif // ADMINLOGIN_H
