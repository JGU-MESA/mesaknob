#ifndef KNOBBOX_H
#define KNOBBOX_H

#include <QFrame>
#include <QList>
#include <QColor>

class Knob;
class QPushButton;
class QEPushButton;
class QECheckBox;
class QEAnalogProgressBar;
class QELabel;
class QESimpleShape;
class QComboBox;
class ValueLabel;

class KnobBox : public QFrame
{
    Q_OBJECT

public:
    explicit KnobBox(QWidget *parent = 0);
    ~KnobBox();
protected:
    QColor buttonColor(bool pressed, int id);
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

    void saveClicked();
    void recallClicked();
    void toggleClicked();
protected:
    double savedValue;
    double toggleValue;
private:
    Knob *knob;
    QPushButton *previousPvButton;
    QPushButton *nextPvButton;
    QComboBox *variableSelection;
    
    QECheckBox *setOutputButton;
    QESimpleShape *getOutputLed;
    QEAnalogProgressBar *getValueLabel;

    QList<QPushButton *> knobButtons;
    QPushButton *shiftLeftButton;
    QPushButton *shiftRightButton;
    ValueLabel *setValueBox;

    QPushButton *saveButton;
    QPushButton *recallButton;
    QPushButton *toggleButton;

    void attachKnob();
    void detachKnob();

};

#endif // KNOBBOX_H
