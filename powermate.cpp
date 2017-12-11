#include <linux/input.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <QDebug>
#include <QTimer>
#include "powermate.h"

PowerMateThread::PowerMateThread(PowerMate *_powerMate, QObject *parent)
	: QThread(parent), powerMate(_powerMate)
{
}

void PowerMateThread::run()
{
	powerMate->loop();
}

PowerMate::PowerMate(int _id, const QString &devicePath, QObject *parent)
    : Knob(_id, parent),
      pressed(false)
{
    deviceFd = open(devicePath.toLocal8Bit().constData(), O_RDWR);
	if (deviceFd < 0)
		qDebug() << "PowerMate: Error opening" << devicePath << ":" << strerror(errno);
	else
		qDebug() << "PowerMate: opened" << devicePath;

	pipe(pipeFd);

	loopThread = new PowerMateThread(this, this);
}

PowerMate::~PowerMate()
{
	loopThread->terminate();
    close(deviceFd);
}

void PowerMate::startLoopThread()
{
	loopThread->start();
}

void PowerMate::processEvent(const struct input_event &event)
{
//	qDebug() << "PowerMate: processEvent, type=" << event.type << "code=" << event.code << "value=" << event.value;
    switch (event.type) {
        case EV_REL:
            if (event.code == REL_DIAL) {
                emit knobRotated(event.value, pressed);
            }
            break;
        case EV_KEY:
            pressed = event.value == 1 ? true : false;
            break;
    }
}

void PowerMate::loop()
{
	qDebug() << "PowerMate: entering loop";
    struct input_event eventBuffer;
	fd_set readfds;
    for (;;) {
		FD_ZERO(&readfds);
		FD_SET(deviceFd, &readfds);
		FD_SET(pipeFd[0], &readfds);
		select((deviceFd > pipeFd[0] ? deviceFd : pipeFd[0]) + 1, &readfds, NULL, NULL, NULL);
		if (FD_ISSET(pipeFd[0], &readfds)) {
			int bytesRead = read(pipeFd[0], &eventBuffer, sizeof(struct input_event));
//			qDebug() << "PowerMate: read" << bytesRead << "bytes from pipe";
			if (bytesRead == sizeof(struct input_event)) {
				write(deviceFd, &eventBuffer, sizeof(struct input_event));
			} else {
				// Fehler werfen
			}
		}
		if (FD_ISSET(deviceFd, &readfds)) {
            int bytesRead = read(deviceFd, &eventBuffer, sizeof(struct input_event));
//			qDebug() << "PowerMate: read" << bytesRead << "bytes from device";
            if (bytesRead > 0) {
                processEvent(eventBuffer);
            } else {
                // Fehler werfen
            }
		}
    }
}

void PowerMate::activate()
{
	const int brightness = 255; // 0 - 255
	const int blinkSpeed = 280; // 0 - 511

	struct input_event ev;
	memset(&ev, 0, sizeof(struct input_event));
	ev.type = EV_MSC;
	ev.code = 0x01;
	ev.value = brightness | (blinkSpeed << 8) | (1 << 19) | (1 << 20);

	write(pipeFd[1], &ev, sizeof(struct input_event));

    QTimer::singleShot(1000, this, &PowerMate::stopBlinking);
}

void PowerMate::stopBlinking()
{
	qDebug() << "PowerMate: stopBlinking";

	struct input_event ev;
	memset(&ev, 0, sizeof(struct input_event));
	ev.type = EV_MSC;
	ev.code = 0x01;
    ev.value = 255;

	write(pipeFd[1], &ev, sizeof(struct input_event));
}

void PowerMate::deactivate()
{
	qDebug() << "PowerMate: deactivate";

	struct input_event ev;
	memset(&ev, 0, sizeof(struct input_event));
	ev.type = EV_MSC;
	ev.code = 0x01;
	ev.value = 0;

	write(pipeFd[1], &ev, sizeof(struct input_event));
}
