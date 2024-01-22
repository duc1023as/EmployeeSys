#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

class DatabaseUtils
{
public:
    DatabaseUtils();
    ~DatabaseUtils();
    bool connectToDB(const QString& dbName);
    QString hashPassword(const QString& password);
    bool checkValidUser(const QString& username,const QString& password);
    QSqlDatabase& getInfoDB() const {return *db;}
private:
    QSqlDatabase *db;
};

#endif // DATABASEUTILS_H
