#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <QString>
#include <QDate>

struct Employee{
    QString fName;
    QString lName;
    QString email;
    QString phone;
    QDate hireDate;
    int jobID;
    QString salary;
    int managerID;
    int departmentID;
};

struct Dependent{
    QString fName;
    QString lName;
    QString realtionship;
    int employee_id;
};

#endif // GLOBALVARIABLES_H
