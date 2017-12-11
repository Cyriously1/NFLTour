#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "admin.h"
#include "adminlogin.h"
#include "tour.h"
#include "userdescription.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class view the NFL teams information and souvenirs
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief displayTeamInfo
     * @param query
     */
    void displayTeamInfo(QSqlQuery query);

    /**
     * @brief displayOpenStadiums
     */
    void displayOpenStadiums();

    /**
     * @brief displayStadiumSeatingCapacities
     */
    void displayStadiumSeatingCapacities();


private slots:

    /**
     * @brief on_lineEdit_searchNflTeams_textEdited
     * @param arg1
     */
    void on_lineEdit_searchNflTeams_textEdited(const QString &arg1);

    /**
     * @brief on_comboBox_nflType_currentIndexChanged
     * @param index
     */
    void on_comboBox_nflType_currentIndexChanged(int index);

    /**
     * @brief on_teamInformation_pushButton_clicked
     */
    void on_teamInformation_pushButton_clicked();

    /**
     * @brief on_pushButton_admin_clicked
     */
    void on_pushButton_admin_clicked();

    /**
     * @brief on_starPlayers_pushButton_clicked
     */
    void on_starPlayers_pushButton_clicked();

    /**
     * @brief on_stadiums_pushButton_clicked
     */
    void on_stadiums_pushButton_clicked();

    /**
     * @brief on_openStadiums_pushButton_clicked
     */
    void on_openStadiums_pushButton_clicked();

    /**
     * @brief on_allStadiums_pushButton_clicked
     */
    void on_allStadiums_pushButton_clicked();

    /**
     * @brief on_SeatingCapacity_pushButton_clicked
     */
    void on_SeatingCapacity_pushButton_clicked();

    /**
     * @brief on_comboBox_sort_currentIndexChanged
     * @param index
     */
    void on_comboBox_sort_currentIndexChanged(int index);

    /**
     * @brief on_pushButton_souvenirs_clicked
     */
    void on_pushButton_souvenirs_clicked();

    /**
     * @brief on_pushButton_trip_clicked
     */
    void on_pushButton_trip_clicked();

    /**
     * @brief on_button_userDescription_clicked
     */
    void on_button_userDescription_clicked();

private:
    /**
     * @brief ui
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
