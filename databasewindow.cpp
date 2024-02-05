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
    DBConnection = QSqlDatabase::database("DBConnector");
    DBConnection.setDatabaseName(path);
    if (DBConnection.open()) {
        qDebug() << "Database is Connected";
    }
    else {
        qDebug() << "Database is Not Connected";
    }
}

DatabaseWindow::~DatabaseWindow()
{
    delete ui;
}

void DatabaseWindow::loginComplete(int _userId) {
    userId = _userId;
    filling = false;
    ui->tableWidget->setColumnWidth(0, 150);
    ui->tableWidget->setColumnWidth(1, 250);
    fillTable(DBConnection);
}

void DatabaseWindow::fillTable(QSqlDatabase DBConnection) {
    if (filling) return;
    filling = true;

    DBConnection = QSqlDatabase::database("DBConnector");
    QSqlQuery query(DBConnection);
    QString tableName = QString::fromStdString("passwordsUser" + std::to_string(userId));
    query.exec("SELECT count(id) FROM " + tableName);
    query.first();
    int rowCount = query.value(0).toInt();
    ui->tableWidget->setRowCount(rowCount);
    // ui->tableWidget->setMaximumHeight(rowCount*(ui->tableWidget->rowHeight(0)+3));
    query.exec("SELECT org, password FROM " + tableName);
    int row = 0;
    while (query.next()) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->comboBox->addItem(query.value(0).toString());
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        row++;
    }
    query.clear();
    filling = false;
}

void DatabaseWindow::on_pushButton_add_clicked()
{
    DBConnection = QSqlDatabase::database("DBConnector");
    QSqlQuery query(DBConnection);
    QString tableName = QString::fromStdString("passwordsUser" + std::to_string(userId));
    QString org = ui->lineEdit_org_add->text();
    QString password = ui->lineEdit_pass_add->text();
    QString theExecStatement = "INSERT INTO " + tableName + " (org, password) VALUES('" + org + "', '" + password + "');";
    query.prepare(theExecStatement);
    if (!query.exec()) {
        qDebug() << "Failed Insertion";
    }
    query.clear();
    ui->comboBox->clear();
    filling = false;
    fillTable(DBConnection);
}


void DatabaseWindow::on_pushButto_delete_clicked()
{
    DBConnection = QSqlDatabase::database("DBConnector");
    QSqlQuery query(DBConnection);
    QString tableName = QString::fromStdString("passwordsUser" + std::to_string(userId));
    QString org = ui->comboBox->currentText();
    QString theExecStatement = "DELETE FROM " + tableName + " WHERE org = '" + org + "';";
    query.prepare(theExecStatement);
    if (!query.exec()) {
        qDebug() << "Failed Insertion";
    }
    query.clear();
    ui->comboBox->clear();
    filling = false;
    fillTable(DBConnection);
}

