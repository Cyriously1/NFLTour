#ifndef ADMINEXTRASPOPUP_H
#define ADMINEXTRASPOPUP_H

#include <QWidget>
#include "admin.h"
#include "graph.h"
#include "database.h"

namespace Ui {
class AdminExtrasPopup;
}

class AdminExtrasPopup : public QWidget
{
    Q_OBJECT

public:
    explicit AdminExtrasPopup(QWidget *parent = 0);
    ~AdminExtrasPopup();

private slots:
    void on_pushButton_back_clicked();

    void on_MST_clicked();

    void on_DFS_clicked();

    void on_BFS_clicked();

private:
    Ui::AdminExtrasPopup *ui;

    Graph *g;
};

#endif // ADMINEXTRASPOPUP_H
