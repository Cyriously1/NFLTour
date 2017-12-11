#include "delegate.h"
#include <QDebug>


Delegate::Delegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}


QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString headerName = index.model()->headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();

    if(headerName == "Price" ||
       headerName == "Distance")
    {
        if(headerName == "Price")
        {
            QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
            editor->setMinimum(0);
            editor->setMaximum(1000);
            return editor;
        }
        else
        {
            QSpinBox *editor = new QSpinBox(parent);
            editor->setMinimum(0);
            editor->setMaximum(5000);
            return editor;
        }
    }
    else if(headerName == "Beginning" ||
            headerName == "Ending" ||
            headerName == "TeamName" ||
            headerName == "StadiumName" ||
            headerName == "Location" ||
            headerName == "StarPlayer" ||
            headerName == "Stadium" ||
            headerName == "Name")
    {
        QRegularExpression expression("[a-zA-Z\\s(,)(.)]+");
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(expression,parent);

        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(validator);
        return editor;
    }
    else if(headerName == "SeatingCapacity")
    {
        QRegularExpression expression("^\\d{1,3}(,\\d{3})*(\\\\d+)?$");
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(expression,parent);

        QLineEdit *editor = new QLineEdit(parent);
        editor->setValidator(validator);
        return editor;
    }
    else
    {
        if(headerName == "Conference")
        {
            QComboBox *editor = new QComboBox(parent);
            editor->addItem("National Football Conference");
            editor->addItem("American Football Conference");
            return editor;
        }
        else if(headerName == "SurfaceType")
        {
            QComboBox *editor = new QComboBox(parent);
            editor->addItem("A-Turf Titan 50 (artificial)"); //0
            editor->addItem("Bandera Bermuda Grass"); //1
            editor->addItem("Desso GrassMaster"); //2
            editor->addItem("FieldTurf Classic HD"); //3
            editor->addItem("FieldTurf Revolution"); //4
            editor->addItem("Hybrid Grass-Synthetic"); //5
            editor->addItem("Kentucky Bluegrass"); //6
            editor->addItem("Latitude 36 Bermuda Grass"); //7
            editor->addItem("Matrix RealGrass artificial turf"); //8
            editor->addItem("Platinum TE Paspalum"); //9
            editor->addItem("Santa Ana Bermuda Grass"); //10
            editor->addItem("TifSport Bermuda Grass"); //11
            editor->addItem("Tifway 419 Bermuda Grass"); //12
            editor->addItem("Tifway II Bermuda Grass"); //13
            editor->addItem("Tifway II Bermuda Grass Perennial Ryegrass mixture"); //14
            editor->addItem("UBU Speed Series S5-M Synthetic Turf"); //15
            editor->addItem("Voyager Bermuda Grass"); //16
            return editor;
        }
        else //if(headerName == "StadiumRoofType")
        {
            QComboBox *editor = new QComboBox(parent);
            editor->addItem("Open");
            editor->addItem("Retractable");
            editor->addItem("Fixed");
            return editor;
        }
    }
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
}


void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString headerName = index.model()->headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();


    if(headerName == "Price" ||
       headerName == "Distance")
    {
        if(headerName == "Price")
        {
            double value = index.model()->data(index, Qt::EditRole).toDouble();
            QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
            spinbox->setValue(value);
        }
        else
        {
            int value = index.model()->data(index, Qt::EditRole).toInt();
            QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
            spinbox->setValue(value);
        }
    }
    else if(headerName == "Beginning" ||
            headerName == "Ending" ||
            headerName == "TeamName" ||
            headerName == "StadiumName" ||
            headerName == "Location" ||
            headerName == "StarPlayer" ||
            headerName == "Stadium" ||
            headerName == "Name")
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(text);
    }
    else if(headerName == "SeatingCapacity")
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(text);
    }
    else
    {
        if(headerName == "Conference")
        {
            int decision;

            QString text = index.model()->data(index, Qt::EditRole).toString();

            if(text == "National Football Conference")
            {
                decision = 0;
            }
            else
            {
                decision = 1;
            }

            QComboBox *comboBox = static_cast<QComboBox*>(editor);
            comboBox->setCurrentIndex(decision);
        }
        else if(headerName == "SurfaceType")
        {
            int decision;

            QString text = index.model()->data(index, Qt::EditRole).toString();

            if(text == "A-Turf Titan 50 (artificial)"){decision = 0;}
            else if(text == "Bandera Bermuda Grass"){decision = 1;}
            else if(text == "Desso GrassMaster"){decision = 2;}
            else if(text == "FieldTurf Classic HD"){decision = 3;}
            else if(text == "FieldTurf Revolution"){decision = 4;}
            else if(text == "Hybrid Grass-Synthetic"){decision = 5;}
            else if(text == "Kentucky Bluegrass"){decision = 6;}
            else if(text == "Latitude 36 Bermuda Grass"){decision = 7;}
            else if(text == "Matrix RealGrass artificial turf"){decision = 8;}
            else if(text == "Platinum TE Paspalum"){decision = 9;}
            else if(text == "Santa Ana Bermuda Grass"){decision = 10;}
            else if(text == "TifSport Bermuda Grass"){decision = 11;}
            else if(text == "Tifway 419 Bermuda Grass"){decision = 12;}
            else if(text == "Tifway II Bermuda Grass"){decision = 13;}
            else if(text == "Tifway II Bermuda Grass Perennial Ryegrass mixture"){decision = 14;}
            else if(text == "UBU Speed Series S5-M Synthetic Turf"){decision = 14;}
            else if(text == "Voyager Bermuda Grass"){decision = 14;}

            QComboBox *comboBox = static_cast<QComboBox*>(editor);
            comboBox->setCurrentIndex(decision);
        }
        else //if (headerName == "StadiumRoofType")
        {
            int decision;

            QString text = index.model()->data(index, Qt::EditRole).toString();

            if(text == "Open")
            {
                decision = 0;
            }
            else if(text == "Retractable")
            {
                decision = 1;
            }
            else //"Fixed"
            {
                decision = 2;
            }

            QComboBox *comboBox = static_cast<QComboBox*>(editor);
            comboBox->setCurrentIndex(decision);
        }
    }
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QString headerName = index.model()->headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();

    if(headerName == "Price" ||
       headerName == "Distance")
    {
        if(headerName == "Price")
        {
            QDoubleSpinBox *spinbox = static_cast<QDoubleSpinBox*>(editor);
            spinbox->interpretText();
            double value = spinbox->value();
            model->setData(index, value, Qt::EditRole);
        }
        else
        {
            QSpinBox *spinbox = static_cast<QSpinBox*>(editor);
            spinbox->interpretText();
            int value = spinbox->value();
            model->setData(index, value, Qt::EditRole);
        }
    }
    else if(headerName == "Beginning" ||
            headerName == "Ending" ||
            headerName == "TeamName" ||
            headerName == "StadiumName" ||
            headerName == "Location" ||
            headerName == "StarPlayer" ||
            headerName == "Stadium" ||
            headerName == "Name")
        {
            QRegularExpression expression("[a-zA-Z\\s(,)(.)]+");
            QRegularExpressionValidator *validator = new QRegularExpressionValidator(expression,this->parent());

            QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
            QString text = lineEdit->text();
            int pos = 0;

            qDebug() << "Text: " << text;
            if(validator->validate(text, pos) == QValidator::Acceptable)
            {
                model->setData(index, text, Qt::EditRole);
            }
            else
            {
                QMessageBox errorMsg;
                errorMsg.setText("Invalid Input");
                errorMsg.exec();

                qDebug() << "Invalid Input";
            }

        }
    else if(headerName == "SeatingCapacity")
    {
        QRegularExpression expression("^\\d{1,3}(,\\d{3})*(\\\\d+)?$");
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(expression,this->parent());

        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString text = lineEdit->text();
        int pos = 0;

        qDebug() << "Text: " << text;
        if(validator->validate(text, pos) == QValidator::Acceptable)
        {
            model->setData(index, text, Qt::EditRole);
        }
        else
        {
            QMessageBox errorMsg;
            errorMsg.setText("Invalid Input");
            errorMsg.exec();

            qDebug() << "Invalid Input";
        }
    }
    else if(headerName == "Conference")
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index,comboBox->currentText(), Qt::EditRole);
    }
    else if(headerName == "SurfaceType")
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index,comboBox->currentText(), Qt::EditRole);
    }
    else //if(headerName == "StadiumRoofType")
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index,comboBox->currentText(), Qt::EditRole);
    }
}


void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
