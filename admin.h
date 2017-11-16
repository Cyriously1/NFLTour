#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "mainwindow.h"
#include "database.h"

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_showTable_clicked();

private:
    Ui::admin *ui;

    Database *database;
};

#endif // ADMIN_H
