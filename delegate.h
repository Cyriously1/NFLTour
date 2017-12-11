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
#include <QMessageBox>

/**
 * @brief The Delegate class user input validation
 */
class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /**
     * @brief Delegate
     * @param parent
     */
    Delegate(QObject *parent = 0);

    /**
     * @brief createEditor
     * @param parent
     * @param option
     * @param index
     * @return
     */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /**
     * @brief paint
     * @param painter
     * @param option
     * @param index
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /**
     * @brief setEditorData
     * @param editor
     * @param index
     */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /**
     * @brief setModelData
     * @param editor
     * @param model
     * @param index
     */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /**
     * @brief updateEditorGeometry
     * @param editor
     * @param option
     * @param index
     */
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:

signals:

public slots:

};

#endif // DELEGATE_H
