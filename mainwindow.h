#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "admin.h"
#include "adminlogin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayTeamInfo(QSqlQuery query);


private slots:

    void on_lineEdit_searchNflTeams_textEdited(const QString &arg1);

    void on_comboBox_nflType_currentIndexChanged(int index);

    void on_teamInformation_pushButton_clicked();

    void on_pushButton_admin_clicked();

    void on_starPlayers_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
