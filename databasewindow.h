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

public slots:
    void loginComplete(int _userId);

private:
    Ui::DatabaseWindow *ui;
    void fillTable(QSqlDatabase DBConnection);
    bool filling;
    int userId = INT_MAX;
};

#endif // DATABASEWINDOW_H
