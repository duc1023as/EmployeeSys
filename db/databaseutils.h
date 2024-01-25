#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "component/querymodel.h"
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QTableView>
#include <QMutex>

class DatabaseUtils
{
public:
    ~DatabaseUtils();
    bool connectToDB(const QString& dbName);
    QString hashPassword(const QString& password);
    bool checkValidUser(const QString& username,const QString& password);
    QSqlDatabase& getInfoDB() const {return *db;}
    QString getTotalEmployee();
    QString getTotalDepartment();
    QString getTotalJob();
    void setEmployeeDetails(QTableView *table);
    void searchEmployeeDetails(QTableView *table,const QString& searchText);
    static DatabaseUtils* getInstance();

private:
    QSqlDatabase *db;
    static DatabaseUtils* instance;
    static QMutex locker;
    DatabaseUtils();
};

#endif // DATABASEUTILS_H
