#include "admin.h"
#include "ui_admin.h"
#include <QWidget>

admin::admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this->parent(), Database::database());

    myDelegate = new Delegate(this);

    QWidget::setWindowTitle("NFL Tour Administration");

    ui->admin_searchBar->setStyleSheet("border-radius: 8px;background: lightgray;");

    //hide the table
    ui->admin_tableview->hide();

    //hide commit button
    ui->admin_commitChanges->hide();

    //hide search
    ui->admin_labelSearch->hide();
    ui->admin_searchBar->hide();
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
    currentTable = "NFLSouvenirs";

    //Show Table elements
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();
    ui->admin_labelSearch->show();
    ui->admin_searchBar->show();

    model->clear();
    model->setTable("NFLSouvenirs");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void admin::on_admin_showNFLInfo_clicked()
{
    currentTable = "NFLInformation";

    //Show Table elements
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();
    ui->admin_labelSearch->show();
    ui->admin_searchBar->show();

    model->clear();
    model->setTable("NFLInformation");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();


    const QModelIndex index = model->index(0, 0);
    model->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void admin::on_admin_showNFLDistances_clicked()
{
    currentTable = "NFLDistances";

    //Show Table elements
    ui->admin_tableview->show();
    ui->admin_commitChanges->show();
    ui->admin_labelSearch->show();
    ui->admin_searchBar->show();

    model->clear();
    model->setTable("NFLDistances");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->admin_tableview->setModel(model);
    ui->admin_tableview->setItemDelegate(myDelegate);
    ui->admin_tableview->resizeColumnsToContents();
    ui->admin_tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->admin_tableview->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}

void admin::on_admin_commitChanges_clicked()
{
    QString tmpStyleSheet = this->styleSheet(); //copy style sheet of admin window
    QMessageBox updateMsg;

    //Customize the QMessageBox
    updateMsg.setText("Are you sure you want to commit changes to the database?");
    updateMsg.setInformativeText("All changes are final.");
    updateMsg.setWindowTitle("Commit Changes");
    updateMsg.setIcon(QMessageBox::Question);
    updateMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    updateMsg.button(QMessageBox::Yes)->setStyleSheet("width: 50px; background: rgba(150,163,220,0.8);");
    updateMsg.button(QMessageBox::No)->setStyleSheet("width: 50px; background: darkgray;");
    updateMsg.setStyleSheet(tmpStyleSheet);

    int decision = updateMsg.exec();

    if(decision == QMessageBox::Yes)
    {
        model->submitAll(); //onManualSubmit edit strategy (Updates the database with changes)
        qDebug() <<"Changes made to the database.";
    }
    else
    {
        qDebug() << "No changes made to the database.";
    }
}

void admin::on_admin_searchBar_textEdited(const QString &arg1)
{
    if(currentTable == "NFLInformation")
    {
        //Filter all columns in NFLInformation table
        model->setFilter("LOWER(TeamName) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(StadiumName) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(SeatingCapacity) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Location) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Conference) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(SurfaceType) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(StadiumRoofType) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(StarPlayer) LIKE '%"+arg1.toLower()+"%'");
    }
    else if(currentTable == "NFLDistances")
    {
        //Filter all columns in NFLDistances table
        model->setFilter("LOWER(Beginning) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Ending) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Distance) LIKE '%"+arg1.toLower()+"%'");
    }
    else //if(currentTable == "NFLSouvenirs")
    {
        //Filter all columns in NFLSouvenirs table
        model->setFilter("LOWER(Stadium) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Name) LIKE '%"+arg1.toLower()+"%' OR "+
                         "LOWER(Price) LIKE '%"+arg1.toLower()+"%'");
    }
}
