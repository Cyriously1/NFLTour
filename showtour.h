#ifndef SHOWTOUR_H
#define SHOWTOUR_H

#include <QWidget>
#include <vector>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>
#include <map>


namespace Ui {
class ShowTour;
}

/**
 * @brief The ShowTour class allows the user to start a tour and purchase souvenirs
 */
class ShowTour : public QWidget
{
    Q_OBJECT

public:
    explicit ShowTour(std::vector<QString> *route, int totalDistance, QWidget *parent = 0);
    ~ShowTour();

    void showSouvenirs();
    void showTeam();
    void deleteSouvenirs();
    void calculateCost();

    void showReciept();


private slots:
    void on_pushButton_next_clicked();

    void on_pushButton_previous_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::ShowTour *ui;

    std::vector<QString> *route;
    int currentIndex = 0;
    double totalCost = 0.0;

    std::vector<QLineEdit*> souvenirQuantityWidgets;    // quantity box widgets
    std::vector<QLabel*> souvenirLabels;                // souvenir label widgets
    std::vector<QLayout*> hLayouts;                     //  souvenir horizontal layouts

    std::map<QString, double> souvenirPriceMap;
    std::vector<QString> souvenirs;

    std::map<QString, double> reciept;      // stadium -> $ spent
};

#endif // SHOWTOUR_H
