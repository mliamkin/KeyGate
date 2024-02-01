#ifndef DATABASEWINDOW_H
#define DATABASEWINDOW_H

#include <QMainWindow>
#include <QtSql/QtSql>
#include <QMessageBox>

namespace Ui {
class DatabaseWindow;
}

class DatabaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DatabaseWindow(QWidget *parent = nullptr);
    ~DatabaseWindow();

private:
    Ui::DatabaseWindow *ui;
    QSqlDatabase DBConnection;
    void fillTable();
    bool filling;
};

#endif // DATABASEWINDOW_H
