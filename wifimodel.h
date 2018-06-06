#ifndef WIFIMODEL_H
#define WIFIMODEL_H

#include <QObject>


class WifiModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameNotify)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordNotify)

public:
    WifiModel(QString name, QString password);
    ~WifiModel();

    QString name() const;
    QString password() const;

    void setName(QString name);
    void setPassword(QString password);

signals:
    void nameNotify();
    void passwordNotify();

private:
    QString m_name;
    QString m_password;
};


#endif // WIFIMODEL_H
