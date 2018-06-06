#ifndef LISTMODEL_H
#define LISTMODEL_H

#include "wifimodel.h"
#include <QAbstractListModel>
#include <QVector>

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    void insert(WifiModel* item);
    void remove(WifiModel* item);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<WifiModel *> mItems;
};

#endif // LISTMODEL_H
