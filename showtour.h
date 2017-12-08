#ifndef SHOWTOUR_H
#define SHOWTOUR_H

#include <QWidget>
#include <vector>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include <QSqlQuery>


namespace Ui {
class ShowTour;
}

class ShowTour : public QWidget
{
    Q_OBJECT

public:
    explicit ShowTour(std::vector<QString> *route, int totalDistance, QWidget *parent = 0);
    ~ShowTour();

    void showSouvenirs();
    void showTeam();
    void deleteSouvenirs();


private slots:
    void on_pushButton_next_clicked();

private:
    Ui::ShowTour *ui;

    std::vector<QString> *route;
    int currentIndex = 0;
    double totalCost = 0.0;

    std::vector<QLineEdit*> souvenirQuantityWidgets;    // quantity box widgets
    std::vector<QLabel*> souvenirLabels;                 // souvenir label widgets
    std::vector<QLayout*> hLayouts;                     //  souvenir horizontal layouts
};

#endif // SHOWTOUR_H
