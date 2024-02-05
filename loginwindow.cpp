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
    databaseWindow = new DatabaseWindow(this);
    QObject::connect(this, SIGNAL(loginComplete(int)), databaseWindow, SLOT(loginComplete(int)));
    loginFunction();
    hide();
    databaseWindow->show();
}

void LoginWindow::loginFunction() {
    //make database if not exist and user table
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
    //query.exec("CREATE TABLE users (id INTEGER NOT NULL UNIQUE, password TEXT UNIQUE,PRIMARY KEY(id))");
    query.prepare("SELECT id FROM users WHERE password='" + password + "';");
    if (query.exec()) {
        int userCount = 0;
        int currentId = 0;
        while (query.next()) {
            currentId = query.value(0).toInt();
            userCount++;
        }
        if (userCount == 1) {
            QMessageBox::information(this, "Login", "Login Successful!");
        }
        else if (userCount == 0) {
            query.exec("INSERT INTO users (password) VALUES ('" + password + "');");
            query.exec("SELECT id FROM users WHERE password='" + password + "';");
            query.next();
            currentId = query.value(0).toInt();
            qDebug() << currentId;
            QString newUserTable = "CREATE TABLE passwordsUser" + QString::number(currentId) + "(org TEXT, password TEXT, id INTEGER UNIQUE, PRIMARY KEY(id));";
            qDebug() << newUserTable;
            if (!query.exec(newUserTable)) {
                qDebug() << "Failure in creating new table";
            }
            QMessageBox::information(this, "Login", "New Database Forming");
        }
        qDebug() << currentId;
        emit loginComplete(currentId);
    }
    else {
        QMessageBox::warning(this, "Login", "Error");
    }
}

