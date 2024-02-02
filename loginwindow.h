#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "databasewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_access_clicked();
    void loginFunction();

signals:
    void loginComplete(int _userId);

private:
    Ui::LoginWindow *ui;
    DatabaseWindow *databaseWindow;
};
#endif // LOGINWINDOW_H
