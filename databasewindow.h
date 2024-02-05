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

private slots:
    void on_pushButton_add_clicked();
    void loginComplete(int _userId);

    void on_pushButto_delete_clicked();

private:
    Ui::DatabaseWindow *ui;
    QSqlDatabase DBConnection;
    void fillTable(QSqlDatabase DBConnection);
    bool filling;
    int userId;
};

#endif // DATABASEWINDOW_H
