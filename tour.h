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

/**
 * @brief The Tour class shows the options for the user to choose their dream vacation
 */
class Tour : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Tour
     * @param parent
     */
    explicit Tour(QWidget *parent = 0);
    ~Tour();

private slots:
    /**
     * @brief on_pushButton_back_clicked
     */
    void on_pushButton_back_clicked();

    /**
     * @brief on_pushButton_add_clicked
     */
    void on_pushButton_add_clicked();

    /**
     * @brief on_pushButton_delete_clicked
     */
    void on_pushButton_delete_clicked();

    /**
     * @brief displayselectedStadiums
     */
    void displayselectedStadiums();

    /**
     * @brief on_button_laTrip_clicked
     */
    void on_button_laTrip_clicked();

    /**
     * @brief on_pushButton_clicked
     */
    void on_pushButton_clicked();

    /**
     * @brief on_button_laStartTour_clicked
     */
    void on_button_laStartTour_clicked();

    /**
     * @brief on_button_customOrder_clicked
     */
    void on_button_customOrder_clicked();

    /**
     * @brief on_button_startTour_clicked
     */
    void on_button_startTour_clicked();

    /**
     * @brief on_button_fordTrip_clicked
     */
    void on_button_fordTrip_clicked();

private:
    /**
     * @brief ui
     */
    Ui::Tour *ui;

    /**
     * @brief selectedStadiums
     */
    std::vector<QString> selectedStadiums;
};

#endif // TOUR_H
