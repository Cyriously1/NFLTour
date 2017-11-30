#ifndef TOUR_H
#define TOUR_H

#include <QDialog>
#include "mainwindow.h"

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

private:
    Ui::Tour *ui;
};

#endif // TOUR_H
