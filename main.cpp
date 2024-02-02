#include "loginwindow.h"
//#include "databasewindow.h"

#include <QApplication>
#include <QtSql/QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow lw;
    DatabaseWindow dw;
    QObject::connect(&lw, SIGNAL(loginComplete(int)), &dw, SLOT(loginComplete(int)));
    lw.show();
    return a.exec();
}
