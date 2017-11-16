#include "admin.h"
#include "ui_admin.h"
#include <QSqlError>
#include <QSqlTableModel>
#include <QWidget>

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("NFL Tour Administration");

    //hide the table
    ui->admin_tableview->hide();
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

    QSqlTableModel *model = new QSqlTableModel(this->parent(), Database::database());
    model->setTable("NFLSouvenirs");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    QSqlQuery query = Database::getInstance()->getTeamInfo();
    query.prepare("SELECT * FROM NFLSouvenirs");

    qDebug() << query.exec();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void admin::on_admin_showNFLInfo_clicked()
{
    ui->admin_tableview->show();

    QSqlTableModel *model = new QSqlTableModel(this->parent(), Database::database());
    model->setTable("NFLInformation");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();


    const QModelIndex index = model->index(0, 0);
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);


    QSqlQuery query = Database::getInstance()->getTeamInfo();
    query.prepare("SELECT * FROM NFLInformation");

    qDebug() << query.exec();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void admin::on_admin_showNFLDistances_clicked()
{
    ui->admin_tableview->show();

    QSqlTableModel *model = new QSqlTableModel(this->parent(), Database::database());
    model->setTable("NFLDistances");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();

    QSqlQuery query = Database::getInstance()->getTeamInfo();
    query.prepare("SELECT * FROM NFLDistances");

    qDebug() << query.exec();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
