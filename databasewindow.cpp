#include "databasewindow.h"
#include "ui_databasewindow.h"

DatabaseWindow::DatabaseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DatabaseWindow)
{
    ui->setupUi(this);

    QDir databasePath;
    QString path = databasePath.currentPath()+"/users.db";
    DBConnection= QSqlDatabase::addDatabase("QSQLITE");
    DBConnection.setDatabaseName(path);
    if (DBConnection.open()) {
        qDebug() << "Database is Connected";
    }
    else {
        qDebug() << "Database is Not Connected";
    }

    filling = false;
    fillTable();
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}

void DatabaseWindow::fillTable() {
    if (filling) return;
    filling = true;

    QSqlQuery query(DBConnection);
    query.exec("SELECT count(id) FROM users");
    query.first();
    ui->tableWidget->setRowCount(query.value(0).toInt());
    qDebug() << query.value(0).toInt();

    query.exec("SELECT id AND passwords FROM users");
    int row = 0;
    for (query.first(); query.isValid(); query.next(), ++row) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        qDebug() << query.value(0).toString();
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        qDebug() << query.value(1).toString();
    }

    filling = false;
}
