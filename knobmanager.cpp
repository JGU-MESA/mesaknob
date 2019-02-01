#include "knobmanager.h"
#include <QSettings>
#include "powermate.h"
#include "main.h"

KnobManager::KnobManager(QObject *parent)
	: QObject(parent)
{
    const int size = settings->beginReadArray("powermate/devices");
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        PowerMate *powerMate = new PowerMate(i, settings->value("path").toString());
        powerMate->startLoopThread();
        powerMate->deactivate();

        knobs.append(powerMate);
    }
    settings->endArray();
}

Knob *KnobManager::getKnob(int knobId)
{
    return knobs.at(knobId);
}

