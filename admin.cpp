#include "admin.h"
#include "ui_admin.h"
#include <QSqlError>
#include <QWidget>

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this->parent(), Database::database());

    myDelegate = new Delegate(this);

    QWidget::setWindowTitle("NFL Tour Administration");

    //hide the table
    ui->admin_tableview->hide();

    //hide commit button
    ui->admin_commitChanges->hide();
}

admin::~admin()
{
    delete ui;
}

void admin::on_pushButton_back_clicked()
{
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

void admin::on_admin_showNFLSouvenirs_clicked()
{
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();

    model->clear();
    model->setTable("NFLSouvenirs");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    QSqlQuery query = Database::getInstance()->getTeamInfo();
    query.prepare("SELECT * FROM NFLSouvenirs");

    qDebug() << query.exec();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void admin::on_admin_showNFLInfo_clicked()
{
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();

    model->clear();
    model->setTable("NFLInformation");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();


    const QModelIndex index = model->index(0, 0);
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);


    QSqlQuery query = Database::getInstance()->getTeamInfo();
    query.prepare("SELECT * FROM NFLInformation");

    qDebug() << query.exec();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void admin::on_admin_showNFLDistances_clicked()
{
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();

    model->clear();
    model->setTable("NFLDistances");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    QSqlQuery query = Database::getInstance()->getTeamInfo();
    query.prepare("SELECT * FROM NFLDistances");

    qDebug() << query.exec();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void admin::on_admin_commitChanges_clicked()
{
//    QString tmpStyleSheet = this->styleSheet();
    QMessageBox updateMsg;
    updateMsg.setText("Are you sure you want to commit changes to the database?");
    updateMsg.setInformativeText("All changes are final.");
    updateMsg.setWindowTitle("Commit Changes");
    updateMsg.setIcon(QMessageBox::Question);
    updateMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    updateMsg.setBaseSize(600,220);
//    updateMsg.setStyleSheet(tmpStyleSheet); // buttons are too small

    int decision = updateMsg.exec();

    if(decision == QMessageBox::Yes)
    {
        model->submitAll();
    }
    else
    {
        qDebug() << "No changes made to the database";
    }
}
