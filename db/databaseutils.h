#ifndef DATABASEUTILS_H
#define DATABASEUTILS_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QTableView>
#include <QMutex>
#include <QComboBox>

#include "component/querymodel.h"
#include "component/comboboxmodel.h"
#include "globalVariables.h"


class DatabaseUtils
{
public:
    ~DatabaseUtils();
    bool connectToDB(const QString& dbName);
    QString hashPassword(const QString& password);
    bool checkValidUser(const QString& username,const QString& password);
    QSqlDatabase& getInfoDB() const {return *db;}
    QString getTotalQuantity(const QString& field,const QString& tableName);
    void setEmployeeDetails(QTableView *table);
    void searchEmployeeDetails(QTableView *table,const QString& searchText);
    void setListForCombobox(QComboBox *combobox,const QString& filed,const QString& tableName);
    QStringList getSalary(const QString &jobTitle);
    int getID(const QString& tableName,const QString& typeID,const QString& field,const QString& value);
    bool addEmployee(const struct Employee& e);
    void getMangerList(QComboBox *combobox,const QString& department);
    static DatabaseUtils* getInstance();
    bool addDependent(const struct Dependent& d);
    int getCurrentEmpID() const;
    void setCurrentEmpID(int newCurrentEmpID);
    int getLastID(const QString& tableName,const QString& field);
    QStringList getInfoEmp(const QString& employee_id);
    bool updateEmployee(const struct Employee& e,const QString& id);

private:
    QSqlDatabase *db;
    static DatabaseUtils* instance;
    static QMutex locker;
    int currentEmpID;
    DatabaseUtils();
};

#endif // DATABASEUTILS_H
