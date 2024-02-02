#include "databasewindow.h"
#include "ui_databasewindow.h"

DatabaseWindow::DatabaseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);

    //Find a way to start db check only after showing this window

    QDir databasePath;
    QString path = databasePath.currentPath()+"/users.db";
    QSqlDatabase DBConnection = QSqlDatabase::database("DBConnector");
    DBConnection.setDatabaseName(path);
    if (DBConnection.open()) {
        qDebug() << "Database is Connected";
    }
    else {
        qDebug() << "Database is Not Connected";
    }
    filling = false;
    fillTable(DBConnection);
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}

void DatabaseWindow::loginComplete(int _userId) {
    userId = _userId;
}

void DatabaseWindow::fillTable(QSqlDatabase DBConnection) {
    if (filling) return;
    filling = true;

    QSqlQuery query(DBConnection);
    query.exec("SELECT count(id) FROM users");
    query.first();
    ui->tableWidget->setRowCount(query.value(0).toInt());
    qDebug() << "What";
    query.exec("SELECT id, password FROM users");
    int row = 0;
    while (query.next()) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        row++;
    }

    filling = false;
}
