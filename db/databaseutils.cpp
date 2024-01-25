#include "databaseutils.h"

DatabaseUtils::DatabaseUtils()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
}

DatabaseUtils::~DatabaseUtils()
{
    delete db;
}

bool DatabaseUtils::connectToDB(const QString& dbName)
{
    db->setDatabaseName(dbName);
    db->setHostName("localhost");
    db->setPort(5432);
    db->setUserName("postgres");
    db->setPassword("doantotnghiep");

    if(db->open()){
        qDebug() << "Connected to database";
        return true;
    }
    else{
        qDebug() << "Failed to connect to database";
        return false;
    }
}

QString DatabaseUtils::hashPassword(const QString &password)
{
    QByteArray bytes = password.toStdString().c_str();
    QString hash = QString(QCryptographicHash::hash(bytes,QCryptographicHash::Md5));
    return hash;
}

bool DatabaseUtils::checkValidUser(const QString &username, const QString &password)
{
    QStringList result;
    QSqlQuery* query = new QSqlQuery(*db);
    query->prepare("SELECT username,hashed_password,user_role FROM user_info WHERE username = '"+username+"';");
    if(query->exec()){
        query->next();
        result.append(query->value(0).toString());
        result.append(query->value(1).toString());
        if(result.at(0).isEmpty()){
            qDebug() << "Username is not exist";
            return false;
        }
        if(result.at(0) == username && result.at(1) == hashPassword(password)){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        qDebug() << "Error:" <<query->lastError().text()<<query->isValid();
        return false;
    }
}

QString DatabaseUtils::getTotalEmployee()
{
    QSqlQuery *query = new QSqlQuery(*db);
    QString result;
    query->prepare("SELECT COUNT(employee_id) FROM employees");
    if(query->exec()){
        qDebug() << "Query successfully";
        query->next();
        result = query->value(0).toString();
    }
    else{
        qDebug()<<query->lastError().text()<<"---"<<query->isValid();
    }
    return result;
}

QString DatabaseUtils::getTotalDepartment()
{
    QSqlQuery *query = new QSqlQuery(*db);
    QString result;
    query->prepare("SELECT COUNT(department_id) FROM departments");
    if(query->exec()){
        qDebug() << "Query successfully";
        query->next();
        result = query->value(0).toString();
    }
    else{
        qDebug()<<query->lastError().text()<<"---"<<query->isValid();
    }
    return result;
}

QString DatabaseUtils::getTotalJob()
{
    QSqlQuery *query = new QSqlQuery(*db);
    QString result;
    query->prepare("SELECT COUNT(job_id) FROM jobs");
    if(query->exec()){
        qDebug() << "Query successfully";
        query->next();
        result = query->value(0).toString();
    }
    else{
        qDebug()<<query->lastError().text()<<"---"<<query->isValid();
    }
    return result;
}

void DatabaseUtils::setEmployeeDetails(QTableView *table)
{
    QueryModel *queryModel = new QueryModel();
    queryModel->setQuery("SELECT e.employee_id,e.first_name,e.last_name,e.email,e.phone_number,j.job_title,d.department_name "
                         "FROM employees e LEFT JOIN jobs j ON j.job_id = e.job_id "
                         "LEFT JOIN departments d ON d.department_id = e.department_id");
    table->setModel(queryModel);
}

void DatabaseUtils::searchEmployeeDetails(QTableView *table, const QString &searchText)
{
    QueryModel *queryModel = new QueryModel();
    queryModel->setQuery("SELECT e.employee_id,e.first_name,e.last_name,e.email,e.phone_number,j.job_title,d.department_name "
                         "FROM employees e "
                         "LEFT JOIN jobs j ON j.job_id = e.job_id  "
                         "LEFT JOIN departments d ON d.department_id = e.department_id "
                         "WHERE e.first_name LIKE '" + searchText + "%';");
    table->setModel(queryModel);
}

DatabaseUtils *DatabaseUtils::getInstance()
{
    locker.lock();
    if(instance == nullptr){
        instance = new DatabaseUtils();
    }
    locker.unlock();
    return instance;
}

DatabaseUtils* DatabaseUtils::instance = nullptr;
QMutex DatabaseUtils::locker;
