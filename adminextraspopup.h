#ifndef ADMINEXTRASPOPUP_H
#define ADMINEXTRASPOPUP_H

#include <QWidget>
#include "admin.h"
#include "graph.h"
#include "database.h"

namespace Ui {
class AdminExtrasPopup;
}

/**
 * @brief The AdminExtrasPopup class allows you to do DFS and BFS searches for any stadiums
 */
class AdminExtrasPopup : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief AdminExtrasPopup
     * @param parent
     */
    explicit AdminExtrasPopup(QWidget *parent = 0);


    ~AdminExtrasPopup();

private slots:
    /**
     * @brief on_pushButton_back_clicked
     */
    void on_pushButton_back_clicked();

    /**
     * @brief on_MST_clicked
     */
    void on_MST_clicked();

    /**
     * @brief on_DFS_clicked
     */
    void on_DFS_clicked();

    /**
     * @brief on_BFS_clicked
     */
    void on_BFS_clicked();

private:
    /**
     * @brief ui
     */
    Ui::AdminExtrasPopup *ui;

    /**
     * @brief g
     */
    Graph *g;
};

#endif // ADMINEXTRASPOPUP_H
