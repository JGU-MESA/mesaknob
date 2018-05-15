#ifndef _PV_LIST_H
#define _PV_LIST_H

#include <QObject>
#include <QList>
#include <QString>
#include <QColor>

class Pv {
private:
    QString setValuePvName;
    QString getValuePvName;
    QString setOutputPvName;
    QString getOutputPvName;
    QString screenName;
    QString description;
    QColor color;
public:
    Pv(const QString &_setValuePvName, const QString &_getValuePvName, const QString &_setOutputPvName, const QString &_getOutputPvName, const QString &_screenName, const QString &_description, const QColor &_color)
        : setValuePvName(_setValuePvName), getValuePvName(_getValuePvName), setOutputPvName(_setOutputPvName), getOutputPvName(_getOutputPvName), screenName(_screenName), description(_description), color(_color) { }
    Pv(const Pv &pv)
        : setValuePvName(pv.setValuePvName), getValuePvName(pv.getValuePvName), setOutputPvName(pv.setOutputPvName), getOutputPvName(pv.getOutputPvName), screenName(pv.screenName), description(pv.description), color(pv.color) { }
    const QString &getSetValuePvName() const { return setValuePvName; }
    const QString &getGetValuePvName() const { return getValuePvName; }
    const QString &getSetOutputPvName() const { return setOutputPvName; }
    const QString &getGetOutputPvName() const { return getOutputPvName; }
    const QString &getScreenName() const { return screenName; }
    const QString &getDescription() const { return description; }
    const QColor &getColor() const { return color; }
};

class PvList : public QObject {
    Q_OBJECT
public:
    PvList(QObject *parent = 0);
    const QList<Pv> &getItems() const { return items; }
protected:
    QList<Pv> items;
signals:
    void contentsChanged();
};

#endif

