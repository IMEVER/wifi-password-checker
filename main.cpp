#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "wifimodel.h"
#include "listmodel.h"

#include <string>
#include <iostream>
#include <QDir>
#include <QSettings>

///etc/NetworkManager/system-connections
///

using namespace std;

ListModel * initList();

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();    

    ListModel* listModel = initList();

    context->setContextProperty("listModel", QVariant::fromValue(listModel));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

ListModel * initList()
{
#ifdef QT_DEBUG
    QString dataPath("/tmp/tmp");
#else
    QString dataPath("/etc/NetworkManager/system-connections");
#endif

    ListModel * listmodel = new ListModel();
    QDir dir(dataPath);
    QStringList fileList = dir.entryList(QDir::Files);
    int i=0, count = fileList.size();
    for (; i < count; i++)
    {
        std::string str = fileList.at(i).toStdString();
        QSettings setting(dataPath + "/" + fileList.at(i), QSettings::IniFormat);
        if (setting.value("connection/type") == "wifi" && setting.contains("wifi-security/psk"))
        {
            listmodel->insert(new WifiModel(setting.value("wifi/ssid").toString(), setting.value("wifi-security/psk").toString()));
        }
    }

    return listmodel;
}
