#ifndef TOUR_H
#define TOUR_H

#include <QDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include "database.h"
#include "graph.h"

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
    void displayselectedStadiums();

    void on_button_startTour_clicked();

    void on_button_laTrip_clicked();

    void on_pushButton_clicked();

    void on_button_laStartTour_clicked();

private:
    Ui::Tour *ui;

    std::vector<QString> selectedStadiums;
};

#endif // TOUR_H
