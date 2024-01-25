#include "querymodel.h"

QueryModel::QueryModel(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QueryModel::~QueryModel()
{

}

QVariant QueryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return QString("Employee ID");
            break;
        case 1:
            return QString("First Name");
            break;
        case 2:
            return QString("Last Name");
            break;
        case 3:
            return QString("Email");
            break;
        case 4:
            return QString("Phone");
            break;
        case 5:
            return QString("Job Title");
            break;
        case 6:
            return QString("Department");
            break;
        }
    }
    if(role == Qt::FontRole && orientation == Qt::Horizontal){
        QFont boldFont;
        boldFont.setBold(true);
        return boldFont;
    }
    if(role == Qt::BackgroundRole && orientation == Qt::Horizontal){
        QBrush fillBackground;
        fillBackground.setColor(Qt::blue);
        return fillBackground;
    }
    return QVariant();
}

//QVariant QueryModel::data(const QModelIndex &item, int role) const
//{

//}
