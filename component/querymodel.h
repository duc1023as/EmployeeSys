#ifndef QUERYMODEL_H
#define QUERYMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include <QFont>
#include <QBrush>

class QueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit QueryModel(QObject *parent = nullptr);
    virtual ~QueryModel();
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
//    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
signals:

};

#endif // QUERYMODEL_H
