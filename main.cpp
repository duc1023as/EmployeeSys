#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show(); //test commit .... ...333 444

    return a.exec();
}
