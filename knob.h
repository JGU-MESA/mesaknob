#ifndef _KNOB_H
#define _KNOB_H

#include <QObject>

class Knob : public QObject {
        Q_OBJECT
private:
    int id;
public:
    Knob(int _id, QObject *parent = 0)
        : QObject(parent), id(_id) { }
	virtual ~Knob() { }

	virtual void activate() { }
	virtual void deactivate() { }
    void unassign() { emit unassignKnob(); }
    int getId() const { return id; }
signals:
	void knobRotated(int delta, bool pressed);
    void unassignKnob();
};

#endif

