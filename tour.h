#ifndef TOUR_H
#define TOUR_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "database.h"

namespace Ui {
class Tour;
}

class Tour : public QDialog
{
    Q_OBJECT

public:
    explicit Tour(QWidget *parent = 0);
    ~Tour();

private slots:
    void on_pushButton_back_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void displaySelectedColleges();

private:
    Ui::Tour *ui;

    QVector<QString> selectedColleges;
};

#endif // TOUR_H
