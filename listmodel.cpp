#include "listmodel.h"

int ListModel::rowCount(const QModelIndex &parent) const {
    return mItems.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const {
    WifiModel* item = mItems.at(index.row());
    return QVariant::fromValue(item);
}

void ListModel::insert(WifiModel *item) {
    beginInsertRows(QModelIndex(), 0, 0);
    mItems.push_front(item);
    endInsertRows();
}

void ListModel::remove(WifiModel *item)
{
    for (int i = 0; i < mItems.size(); i++)
    {
        if (mItems.at(i) == item)
        {
            beginRemoveRows(QModelIndex(), i, i);
            mItems.remove(i);
            endRemoveRows();
            break;
        }
    }
}

QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "item";
    return roles;
}
