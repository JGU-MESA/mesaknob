#include "mainwindow.h"
#include "main.h"
#include "knobmanager.h"
#include "pv_list.h"
#include <QApplication>
#include <QSettings>

QSettings *settings;
KnobManager *knobManager;
PvList *pvList;

int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
	settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "MESA", "Knob");
/*
settings->beginWriteArray("powermate/devices");
settings->setArrayIndex(0);
settings->setValue("path", "/dev/input/by-path/pci-0000:00:1d.0-usb:1.1:1.0-event");
settings->endArray();
*/
	knobManager = new KnobManager();
    pvList = new PvList();

        MainWindow w;
        w.show();
        
        return a.exec();
}
