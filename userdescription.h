#ifndef USERDESCRIPTION_H
#define USERDESCRIPTION_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class UserDescription;
}

/**
 * @brief The UserDescription class shows the description for the program
 */
class UserDescription : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief UserDescription
     * @param parent
     */
    explicit UserDescription(QWidget *parent = 0);
    ~UserDescription();

private slots:
    /**
     * @brief on_button_back_clicked
     */
    void on_button_back_clicked();

private:
    /**
     * @brief ui
     */
    Ui::UserDescription *ui;
};

#endif // USERDESCRIPTION_H
