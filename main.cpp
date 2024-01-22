#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show(); //test commit .... ...333 444

//    QSqlDatabase *db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
//    db->setDatabaseName("web_iot");
//    db->setHostName("localhost");
//    db->setPort(5432);
//    db->setUserName("postgres");
//    db->setPassword("doantotnghiep");

//    if(db->open()){
//        qDebug()<<"Connected to Database";
//    }

    return a.exec();
}
