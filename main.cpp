#include "loginwindow.h"
//#include "databasewindow.h"

#include <QApplication>
#include <QtSql/QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow lw;
    DatabaseWindow dw;
    lw.show();
    return a.exec();
}
