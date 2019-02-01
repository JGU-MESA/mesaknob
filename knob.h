#ifndef _KNOB_H
#define _KNOB_H

#include <QObject>

class Knob : public QObject {
    Q_OBJECT
private:
    int id;
    int numClients;
public:
    Knob(int _id, QObject *parent = 0);
    virtual ~Knob() { };

    virtual void activate() = 0;
    virtual void deactivate() = 0;
    void unassign();
    int getId() const { return id; }

    void addClient();
    void removeClient();
signals:
    void knobRotated(int delta, bool pressed);
    void unassignKnob();
};

#endif

