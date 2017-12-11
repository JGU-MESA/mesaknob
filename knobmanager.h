#ifndef _KNOBMANAGER_H
#define _KNOBMANAGER_H

/*
 * This should be an abstract class to support different types of knobs
 */

#include <QObject>
#include <QList>

class Knob;

class KnobManager : public QObject {
	Q_OBJECT
protected:
	QList<Knob *> knobs;
public:
	KnobManager(QObject *parent = 0);
	int getKnobCount() const { return knobs.size(); }
	Knob *registerKnob(int knobId);
signals:
    void detachKnob(int knobId);
};

#endif
