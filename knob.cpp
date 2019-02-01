#include "knob.h"

Knob::Knob(int _id, QObject *parent)
    : QObject(parent),
      id(_id),
      numClients(0)
{
}

void Knob::addClient()
{
    if (numClients++ == 0)
        activate();
}

void Knob::removeClient()
{
    if (--numClients == 0)
        deactivate();
}

void Knob::unassign()
{
    emit unassignKnob();
}
