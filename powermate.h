#ifndef POWERMATE_H
#define POWERMATE_H

#include <QThread>
#include "knob.h"

struct input_event;
class PowerMate;

class PowerMateThread : public QThread
{
	Q_OBJECT
public:
	PowerMateThread(PowerMate *_powerMate, QObject *parent = 0);
private:
	PowerMate *powerMate;
protected:
	void run();
};

class PowerMate : public Knob
{
    Q_OBJECT
public:
    explicit PowerMate(int _id, const QString &devicePath, QObject *parent = 0);
    virtual ~PowerMate();

	void activate();
	void deactivate();
	void startLoopThread();
private:
	PowerMateThread *loopThread;
        int deviceFd;
	int pipeFd[2];
	void stopBlinking();
protected:
    void processEvent(const struct input_event &event);
    bool pressed;
public slots:
    void loop();
};

#endif // POWERMATE_H
