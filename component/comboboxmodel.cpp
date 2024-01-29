#include "comboboxmodel.h"

ComboboxModel::ComboboxModel()
{

}

ComboboxModel::~ComboboxModel()
{

}

int ComboboxModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return listData.length();
}

QVariant ComboboxModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole && index.row() < listData.length()){
        return listData.at(index.row());
    }
    return QVariant();
}

QStringList ComboboxModel::getListData() const
{
    return listData;
}

void ComboboxModel::setListData(const QStringList &newListData)
{
    listData = newListData;
}
