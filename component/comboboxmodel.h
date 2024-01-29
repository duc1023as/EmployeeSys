#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QAbstractListModel>

class ComboboxModel : public QAbstractListModel
{
public:
    ComboboxModel();
    ~ComboboxModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,int role) const override;
    QStringList getListData() const;
    void setListData(const QStringList &newListData);

private:
    QStringList listData;
};

#endif // COMBOBOXMODEL_H
