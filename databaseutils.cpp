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

