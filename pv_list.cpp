#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QFile>
#include "pv_list.h"
#include "main.h"
#include <QDebug>
#include <iostream>

PvList::PvList(QObject *parent)
    : QObject(parent)
{
    QString pvFileName = settings->value("pv_list").toString();
    QFile pvFile(pvFileName);
    if (!pvFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Unable to open PV list: " << pvFileName.toStdString() << std::endl;
        return;
    }
    QJsonDocument json = QJsonDocument::fromJson(pvFile.readAll());
    QJsonArray rootElement = json.object().value("pvs").toArray();
    for (QJsonArray::const_iterator i = rootElement.constBegin(); i != rootElement.constEnd(); ++i) {
        QJsonObject obj = i->toObject();
        items.append(Pv(obj.value("set").toString(),
                        obj.value("get").toString(),
                        obj.value("onset").toString(),
                        obj.value("onget").toString(),
                        obj.value("name").toString(),
                        obj.value("desc").toString(),
                        QColor(obj.value("color").toString())));
    }
}

