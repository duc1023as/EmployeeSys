#include "databaseutils.h"

DatabaseUtils::DatabaseUtils()
{
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QPSQL"));
}

DatabaseUtils::~DatabaseUtils()
{
    delete db;
    delete instance;
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
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    //QSqlQuery* query = new QSqlQuery(*db);
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

QString DatabaseUtils::getTotalQuantity(const QString& field,const QString& tableName)
{
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    //QSqlQuery *query = new QSqlQuery(*db);
    QString result;
    query->prepare("SELECT COUNT(" + field + ") FROM "+tableName);
    if(query->exec()){
        qDebug() << "Query successfully "<<field;
        query->next();
        result = query->value(0).toString();
    }
    else{
        qDebug()<<field<<query->lastError().text()<<"---"<<query->isValid();
    }
    return result;
}

void DatabaseUtils::setEmployeeDetails(QTableView *table)
{ 
    QueryModel *queryModel = new QueryModel();
    queryModel->setQuery("SELECT e.employee_id,e.first_name,e.last_name,e.email,e.phone_number,j.job_title,d.department_name,m.first_name "
                         "FROM employees e "
                         "LEFT JOIN jobs j ON j.job_id = e.job_id "
                         "LEFT JOIN departments d ON d.department_id = e.department_id "
                         "LEFT JOIN employees m ON m.employee_id = e.manager_id "
                         "ORDER BY e.employee_id");
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

void DatabaseUtils::setListForCombobox(QComboBox *combobox,const QString& filed,const QString& tableName)
{
    QStringList result;
    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    ComboboxModel *model = new ComboboxModel();
    query->prepare("SELECT "+filed+ " FROM "+tableName);
    if(query->exec()){
        while(query->next()){
            result.push_back(query->value(0).toString());
        }
    }
    else{
        qDebug() << query->lastError().text()<<"----"<<query->isValid();
    }
    model->setListData(result);
    combobox->setModel(model);
}

QStringList DatabaseUtils::getSalary(const QString &jobTitle)
{
    QStringList result;
    //QSqlQuery *query =  new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    query->prepare("SELECT min_salary,max_salary FROM jobs WHERE job_title='"+jobTitle+"'");
    if(query->exec()){
        query->next();
        result.push_back(query->value(0).toString());
        result.push_back(query->value(1).toString());
    }
    else{
        qDebug() << query->lastError().text()<<"---"<<query->isValid();
    }
    return result;
}

int DatabaseUtils::getID(const QString &tableName, const QString &typeID, const QString &field, const QString &value)
{

    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    int id;
    query->prepare("SELECT "+typeID+" FROM "+tableName+" WHERE "+field+" ='"+value+"'");
    query->exec();
    query->next();
    id = query->value(0).toInt();
    return id;
}

bool DatabaseUtils::addEmployee(const Employee &e)
{
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    //QSqlQuery* query = new QSqlQuery();
    //QString test = "INSERT INTO employees(first_name,last_name,email,phone_number,hire_date,job_id,salary,manager_id,department_id) VALUES('"+e.fName+"','"+e.lName+"','"+e.email+"','"+e.phone+"',"+e.hireDate.toString()+","+QString::number(e.jobID)+","+e.salary+","+QString::number(e.managerID)+","+QString::number(e.departmentID)+")";;
    int lastID = getLastID("employees","employee_id");
    query->prepare("INSERT INTO employees(employee_id,first_name,last_name,email,phone_number,hire_date,job_id,salary,manager_id,department_id) "
                   "VALUES("+QString::number(++lastID)+",'"+e.fName+"','"+e.lName+"','"+e.email+"','"+e.phone+"','"
                   +e.hireDate.toString()+"',"+QString::number(e.jobID)+","+e.salary
                   +","+QString::number(e.managerID)+","+QString::number(e.departmentID)+") RETURNING employee_id");
    //qDebug() << test;
    if(query->exec()){
        query->next();
        currentEmpID = query->value(0).toInt();
        qDebug() << "Inserted successfully";
        return true;
    }
    else{
        qDebug() << query->lastError().text()<<"---"<<query->isValid();
        return false;
    }
}

void DatabaseUtils::getMangerList(QComboBox *combobox,const QString& department)
{
    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    QStringList result;
    ComboboxModel *comboModel = new ComboboxModel();
    int departmentID = getID("departments","department_id","department_name",department);
    query->prepare("SELECT first_name FROM employees WHERE department_id="+QString::number(departmentID));
    if(query->exec()){
        while(query->next()){
            result.push_back(query->value(0).toString());
        }
    }
    else{
        qDebug() << query->lastError().text()<<"---"<<query->isValid();
    }
    comboModel->setListData(result);
    combobox->setModel(comboModel);
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

bool DatabaseUtils::addDependent(const Dependent &d)
{
    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    int lastId = getLastID("dependents","dependent_id");
    qDebug() << "Last index dependets:"<<lastId;
    query->prepare("INSERT INTO dependents(dependent_id,first_name,last_name,relationship,employee_id) VALUES("+QString::number(++lastId)+",'"+d.fName+"','"+d.lName+"','"+d.realtionship+"',"+QString::number(d.employee_id)+")");
    if(query->exec()){
        qDebug()<<"Insert dependent successfully";
        return true;
    }
    else{
        qDebug() << query->lastError().text()<<"---"<<query->isValid();
        return false;
    }
}

int DatabaseUtils::getCurrentEmpID() const
{
    return currentEmpID;
}

void DatabaseUtils::setCurrentEmpID(int newCurrentEmpID)
{
    currentEmpID = newCurrentEmpID;
}

int DatabaseUtils::getLastID(const QString &tableName, const QString &field)
{
    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    int lastId;
    query->prepare("SELECT MAX("+field+") FROM "+tableName);
    query->exec();
    query->next();
    lastId = query->value(0).toInt();
    qDebug() << "Last index "+tableName+":"<<lastId;
    return lastId;
}

QStringList DatabaseUtils::getInfoEmp(const QString &employee_id)
{
    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    QStringList result;
    query->prepare("SELECT e.first_name,e.last_name,e.email,e.phone_number,e.hire_date,j.job_title,e.salary,e1.first_name,d.department_name "
                   "FROM employees e  "
                   "LEFT JOIN jobs j ON j.job_id = e.job_id  "
                   "LEFT JOIN departments d ON d.department_id = e.department_id "
                   "LEFT JOIN employees e1 ON e1.employee_id = e.manager_id "
                   "WHERE e.employee_id ="+employee_id);
    query->exec();
    query->next();
    for(int i=0;i<9;i++){
        result.push_back(query->value(i).toString());
    }
    return result;
}

bool DatabaseUtils::updateEmployee(const Employee &e,const QString& id)
{
    //QSqlQuery *query = new QSqlQuery();
    QScopedPointer<QSqlQuery> query(new QSqlQuery(*db));
    query->prepare("UPDATE employees SET first_name='"
                   +e.fName+"',last_name='"+e.lName+"',email='"+e.email+"',phone_number='"
                   +e.phone+"',hire_date='"+e.hireDate.toString()
                   +"',job_id="+QString::number(e.jobID)+",salary="
                   +e.salary+",manager_id="+QString::number(e.managerID)
                   +",department_id="+QString::number(e.departmentID)
                   +" WHERE employee_id="+id);
    qDebug()<<("UPDATE employees SET first_name='"
                   +e.fName+"',last_name='"+e.lName+"',email='"+e.email+"',phone_number='"
                   +e.phone+"',hire_date='"+e.hireDate.toString()
                   +"',job_id="+QString::number(e.jobID)+",salary="
                   +e.salary+",manager_id="+QString::number(e.managerID)
                   +",department_id="+QString::number(e.departmentID)
                   +" WHERE employee_id="+id);
    if(query->exec()){
        qDebug()<<"Update successfully";
        return true;
    }
    else{
        qDebug()<<"Failed to update";
        return false;
    }
}

DatabaseUtils* DatabaseUtils::instance = nullptr;
QMutex DatabaseUtils::locker;
