#ifndef KNOBBOX_H
#define KNOBBOX_H

#include <QFrame>
#include <QList>

class Knob;
class QPushButton;
class QEPushButton;
class QECheckBox;
class QEAnalogProgressBar;
class QELabel;
class QComboBox;
class ValueLabel;

class KnobBox : public QFrame
{
    Q_OBJECT

public:
    explicit KnobBox(QWidget *parent = 0);
    ~KnobBox();

private slots:
    void knobButtonToggled();
    void assignKnob();
    void unassignKnob();
    void previousPv();
    void nextPv();
    void updatePvList();
    void disableControls();
    void enableControls();
    void pvSelected(int index);
    void knobRotated(int delta, bool pressed);
private:
    Knob *knob;
    QPushButton *previousPvButton;
    QPushButton *nextPvButton;
    QComboBox *variableSelection;
    
    QECheckBox *setOutputButton;
    QELabel *getOutputLabel;
    QEAnalogProgressBar *getValueLabel;

    QList<QPushButton *> knobButtons;
    QPushButton *shiftLeftButton;
    QPushButton *shiftRightButton;
    ValueLabel *setValueBox;

    void attachKnob();
    void detachKnob();

};

#endif // KNOBBOX_H
