#include "loginwindow.h"
#include "./ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_access_clicked()
{
    loginFunction();
    hide();
    databaseWindow = new DatabaseWindow(this);
    databaseWindow->show();
}

void LoginWindow::loginFunction() {
    QDir databasePath;
    QString path = databasePath.currentPath()+"/users.db";
    QSqlDatabase DBConnection =  QSqlDatabase::addDatabase("QSQLITE", "DBConnector");
    DBConnection.setDatabaseName(path);
    if (DBConnection.open()) {
        qDebug() << "Database is Connected";
    }
    else {
        qDebug() << "Database is Not Connected";
    }
    QString password = ui->lineEdit_password->text();
    QSqlQuery query(DBConnection);
    query.prepare("SELECT id FROM users WHERE password='" + password + "';");
    if (query.exec()) {
        int userCount = 0;
        int currentId = 0;
        while (query.next()) {
            currentId = query.value(0).toInt();
            userCount++;
        }
        if (userCount == 1) {
            qDebug() << "Id is " << currentId;
            QMessageBox::information(this, "Login", "Login Successful!");
        }
        else if (userCount == 0) {
            qDebug() << "New user adding";
            QMessageBox::information(this, "Login", "New Database Forming");
        }
    }
    else {
        QMessageBox::warning(this, "Login", "Error");
    }
    DBConnection.close();
}

