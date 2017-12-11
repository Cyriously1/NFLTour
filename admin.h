#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "mainwindow.h"
#include "database.h"
#include <QSqlTableModel>
#include "delegate.h"
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

namespace Ui {
class admin;
}

/**
 * @brief The admin class allows you to do administrative duties
 */
class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();

private slots:
    /**
     * @brief on_pushButton_back_clicked
     */
    void on_pushButton_back_clicked();

    /**
     * @brief on_admin_showNFLSouvenirs_clicked
     */
    void on_admin_showNFLSouvenirs_clicked();

    /**
     * @brief on_admin_showNFLInfo_clicked
     */
    void on_admin_showNFLInfo_clicked();

    /**
     * @brief on_admin_showNFLDistances_clicked
     */
    void on_admin_showNFLDistances_clicked();

    /**
     * @brief on_admin_commitChanges_clicked
     */
    void on_admin_commitChanges_clicked();

    /**
     * @brief on_admin_searchBar_textEdited
     * @param arg1
     */
    void on_admin_searchBar_textEdited(const QString &arg1);

    /**
     * @brief on_admin_tableview_clicked
     * @param index
     */
    void on_admin_tableview_clicked(const QModelIndex &index);

    /**
     * @brief on_admin_deleteSouvenir_clicked
     */
    void on_admin_deleteSouvenir_clicked();

    /**
     * @brief on_admin_addSouvenir_clicked
     */
    void on_admin_addSouvenir_clicked();

    /**
     * @brief on_admin_newSouvName_textEdited
     * @param arg1
     */
    void on_admin_newSouvName_textEdited(const QString &arg1);

    /**
     * @brief on_admin_addSouvenirFinal_clicked
     */
    void on_admin_addSouvenirFinal_clicked();

    /**
     * @brief on_admin_addSailors_clicked
     */
    void on_admin_addSailors_clicked();

    /**
     * @brief on_admin_moveRams_clicked
     */
    void on_admin_moveRams_clicked();

    /**
     * @brief on_pushButton_extras_clicked
     */
    void on_pushButton_extras_clicked();

private:
    /**
     * @brief ui
     */
    Ui::admin *ui;

    /**
     * @brief model
     */
    QSqlTableModel *model;

    /**
     * @brief database
     */
    Database *database;

    /**
     * @brief myDelegate
     */
    Delegate *myDelegate;

    /**
     * @brief currentTable
     */
    QString currentTable;

    /**
     * @brief souvSelectionRow
     */
    int souvSelectionRow;

    /**
     * @brief newSouvName
     */
    QString newSouvName, newSouvPrice;
};

#endif // ADMIN_H
