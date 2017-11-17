#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "mainwindow.h"
#include "database.h"
#include <QSqlTableModel>
#include "delegate.h"
#include <QMessageBox>
#include <QSortFilterProxyModel>

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = 0);
    ~admin();

private slots:
    void on_pushButton_back_clicked();

    void on_admin_showNFLSouvenirs_clicked();

    void on_admin_showNFLInfo_clicked();

    void on_admin_showNFLDistances_clicked();

    void on_admin_commitChanges_clicked();

    void on_admin_searchBar_textEdited(const QString &arg1);

private:
    Ui::admin *ui;

    QSqlTableModel *model;

    Database *database;

    Delegate *myDelegate;

    QString currentTable;
};

#endif // ADMIN_H
