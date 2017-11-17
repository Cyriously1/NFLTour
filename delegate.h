#ifndef DELEGATE_H
#define DELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QSize>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    Delegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
//    QString headerName;

signals:

public slots:

};

#endif // DELEGATE_H
