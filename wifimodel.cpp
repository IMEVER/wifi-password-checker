#include "wifimodel.h"

WifiModel::WifiModel(QString name, QString password) : QObject()
{
    this->m_name = name;
    this->m_password = password;
}

WifiModel::~WifiModel() {

}

QString WifiModel::name() const
{
    return m_name;
}

QString WifiModel::password() const
{
    return m_password;
}

void WifiModel::setName(QString name)
{
    this->m_name = name;
}

void WifiModel::setPassword(QString password)
{
    this->m_password = password;
}
