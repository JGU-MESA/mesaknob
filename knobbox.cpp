#include "knobbox.h"
#include "main.h"
#include "knob.h"
#include "knobmanager.h"
#include "pv_list.h"
#include "value_label.h"
#include <QELabel.h>
#include <QEAnalogProgressBar.h>
#include <QEPushButton.h>
#include <QECheckBox.h>
#include <QESimpleShape.h>
#include <QtWidgets>
#include <QDebug>

QColor KnobBox::buttonColor(bool pressed, int id)
{
    switch (id) {
        case 0: return pressed ? QColor(255, 0, 0) : QColor(255, 230, 230);
        case 1: return pressed ? QColor(0, 255, 0) : QColor(230, 255, 230);
        case 2: return pressed ? QColor(0, 0, 255) : QColor(230, 230, 255);
        case 3: return pressed ? QColor(255, 255, 0) : QColor(255, 255, 230);
        default: return Qt::white;
    }
}

KnobBox::KnobBox(QWidget *parent) :
    QFrame(parent), savedValue(0), toggleValue(0), knob(0)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    previousPvButton = new QPushButton("<");
    nextPvButton = new QPushButton(">");
    connect(previousPvButton, SIGNAL(clicked()), this, SLOT(previousPv()));
    connect(nextPvButton, SIGNAL(clicked()), this, SLOT(nextPv()));

    variableSelection = new QComboBox;
    QFont variableSelectionFont;
//    variableSelectionFont.setPointSize(14);
    variableSelectionFont.setWeight(QFont::Bold);
    variableSelection->setFont(variableSelectionFont);
    variableSelection->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    updatePvList();
    connect(pvList, &PvList::contentsChanged, this, &KnobBox::updatePvList);
    connect(variableSelection, SIGNAL(currentIndexChanged(int)), this, SLOT(pvSelected(int)));

    QHBoxLayout *variableSelectionLayout = new QHBoxLayout;
    variableSelectionLayout->addWidget(previousPvButton);
    variableSelectionLayout->addWidget(variableSelection);
    variableSelectionLayout->addWidget(nextPvButton);

    shiftLeftButton = new QPushButton("* 10");
    shiftLeftButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    setValueBox = new ValueLabel();
    setValueBox->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
    QFont valueBoxFont;
    valueBoxFont.setPointSize(20);
    valueBoxFont.setWeight(QFont::Bold);
    valueBoxFont.setFamily("Monospace");
    setValueBox->setFont(valueBoxFont);
    connect(setValueBox, &ValueLabel::dataValid, this, &KnobBox::saveClicked);
    shiftRightButton = new QPushButton("/ 10");
    shiftRightButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    connect(shiftLeftButton, SIGNAL(clicked()), setValueBox, SLOT(shiftLeft()));
    connect(shiftRightButton, SIGNAL(clicked()), setValueBox, SLOT(shiftRight()));

    QHBoxLayout *setValueLayout = new QHBoxLayout;
    setValueLayout->addWidget(shiftLeftButton);
    setValueLayout->addWidget(setValueBox);
    setValueLayout->addWidget(shiftRightButton);

    setOutputButton = new QECheckBox;
    setOutputButton->setCheckable(true);
    setOutputButton->setSubscribe(true);
    setOutputButton->setClickText("OFF");
    setOutputButton->setClickCheckedText("ON");
    setOutputButton->setText("Output");
    getOutputLed = new QESimpleShape;
    getOutputLed->setDisplayAlarmStateOptionProperty(QESimpleShape::Never);
    getOutputLed->setTextFormat(QSimpleShape::PvText);
    getOutputLed->setShape(QSimpleShape::rectangle);
    getOutputLed->setColour0Property(Qt::gray);
    getOutputLed->setColour1Property(Qt::green);
    getValueLabel = new QEAnalogProgressBar;
    getValueLabel->setUseDbDisplayLimits(true);
    
    QHBoxLayout *miscLayout = new QHBoxLayout;
    miscLayout->addWidget(setOutputButton);
    miscLayout->addWidget(getOutputLed);
    miscLayout->addWidget(getValueLabel);

    QHBoxLayout *assignKnobLayout = new QHBoxLayout;
    for (int i = 0; i < knobManager->getKnobCount(); ++i) {
        QPushButton *button = new QPushButton(QString::number(i));
        button->setCheckable(true);
        QPalette p = button->palette();
        p.setColor(QPalette::Active, QPalette::Button, buttonColor(false, i));
        p.setColor(QPalette::Inactive, QPalette::Button, buttonColor(false, i));
        button->setPalette(p);
        button->setMinimumHeight(40);
        connect(button, &QPushButton::toggled, this, &KnobBox::knobButtonToggled);
        knobButtons.append(button);
        assignKnobLayout->addWidget(button);
    }

    saveButton = new QPushButton("Save");
    saveButton->setMinimumHeight(40);
    connect(saveButton, &QPushButton::clicked, this, &KnobBox::saveClicked);
    recallButton = new QPushButton("Recall\n---");
    recallButton->setMinimumHeight(40);
    connect(recallButton, &QPushButton::clicked, this, &KnobBox::recallClicked);
    toggleButton = new QPushButton("Toggle\n---");
    toggleButton->setMinimumHeight(40);
    connect(toggleButton, &QPushButton::clicked, this, &KnobBox::toggleClicked);

    QHBoxLayout *saveRecallLayout = new QHBoxLayout;
    saveRecallLayout->addWidget(saveButton);
    saveRecallLayout->addWidget(recallButton);
    saveRecallLayout->addWidget(toggleButton);

    QVBoxLayout *completeLayout = new QVBoxLayout;
    completeLayout->addLayout(variableSelectionLayout);
    completeLayout->addLayout(setValueLayout);
    completeLayout->addLayout(miscLayout);
    completeLayout->addLayout(saveRecallLayout);
    completeLayout->addLayout(assignKnobLayout);

    setLayout(completeLayout);
    disableControls();
}

KnobBox::~KnobBox()
{

}

void KnobBox::disableControls()
{
    shiftLeftButton->setEnabled(false);
    shiftRightButton->setEnabled(false);
    setValueBox->setEnabled(false);
    setOutputButton->setEnabled(false);
    getOutputLed->setEnabled(false);
    getValueLabel->setEnabled(false);
}

void KnobBox::enableControls()
{
    shiftLeftButton->setEnabled(true);
    shiftRightButton->setEnabled(true);
    setValueBox->setEnabled(true);
    setOutputButton->setEnabled(true);
    getOutputLed->setEnabled(true);
    getValueLabel->setEnabled(true);
}

void KnobBox::previousPv()
{
    variableSelection->setCurrentIndex(variableSelection->currentIndex() - 1);
}

void KnobBox::nextPv()
{
    variableSelection->setCurrentIndex(variableSelection->currentIndex() + 1);
}

void KnobBox::updatePvList()
{
    variableSelection->clear();
    variableSelection->addItem("---");

    const QList<Pv> &items = pvList->getItems();
    for (QList<Pv>::const_iterator i = items.constBegin(); i != items.constEnd(); ++i) {
        variableSelection->addItem(i->getScreenName());
    }
    previousPvButton->setEnabled(false);
    nextPvButton->setEnabled(true);
}

void KnobBox::pvSelected(int index)
{
    if (index <= 0) {
        setValueBox->setVariableNameProperty(QString());
        setOutputButton->setVariableNameProperty(QString());
        getOutputLed->setVariableNameProperty(QString());
        getValueLabel->setVariableNameProperty(QString());
        disableControls();
    } else {
        const Pv &pv = pvList->getItems().at(index - 1);
        setValueBox->setVariableNameProperty(pv.getSetValuePvName());
        setOutputButton->setVariableNameProperty(pv.getSetOutputPvName());
        getOutputLed->setVariableNameProperty(pv.getGetOutputPvName());
        getValueLabel->setVariableNameProperty(pv.getGetValuePvName());
        enableControls();
    }
    savedValue = 0;
    recallButton->setText("Recall\n---");
    toggleValue = 0;
    toggleButton->setText("Toggle\n---");
    previousPvButton->setEnabled(index > 0);
    nextPvButton->setEnabled(index < pvList->getItems().size());
}

void KnobBox::knobButtonToggled()
{
    QPushButton *button = static_cast<QPushButton *>(sender());
    QPalette p = button->palette();
    p.setColor(QPalette::Active, QPalette::Button, buttonColor(button->isChecked(), button->text().toInt()));
    p.setColor(QPalette::Inactive, QPalette::Button, buttonColor(button->isChecked(), button->text().toInt()));
    button->setPalette(p);
        
    if (button->isChecked()) {
        if (knob)
            unassignKnob();
        assignKnob();
    } else
        detachKnob();
}

void KnobBox::assignKnob()
{
    qDebug() << "assignKnob";
    knob = knobManager->registerKnob(static_cast<QPushButton *>(sender())->text().toInt());
    attachKnob();
}

void KnobBox::attachKnob()
{
    qDebug() << "attachKnob";
    connect(knob, &Knob::unassignKnob, this, &KnobBox::unassignKnob);
    connect(knob, &Knob::knobRotated, this, &KnobBox::knobRotated);
}

void KnobBox::unassignKnob()
{
    knobButtons.at(knob->getId())->setChecked(false);
}

void KnobBox::detachKnob()
{
    disconnect(knob, &Knob::unassignKnob, this, &KnobBox::unassignKnob);
    disconnect(knob, &Knob::knobRotated, this, &KnobBox::knobRotated);
    knob->deactivate();
    knob = 0;
}

void KnobBox::knobRotated(int delta, bool pressed)
{
    if (pressed) {
        if (delta > 0)
            setValueBox->shiftRight();
        else
            setValueBox->shiftLeft();
    } else
        setValueBox->setValue(setValueBox->getCurrentValue() + delta * pow(10, setValueBox->getExponent()));
}

void KnobBox::saveClicked()
{
    savedValue = setValueBox->getCurrentValue();
    recallButton->setText(QString("Recall\n%1").arg(setValueBox->formatNumber(false, false)));
    toggleValue = setValueBox->getCurrentValue();
    toggleButton->setText(QString("Toggle\n%1").arg(setValueBox->formatNumber(false, false)));
}

void KnobBox::recallClicked()
{
    setValueBox->setValue(savedValue);
}

void KnobBox::toggleClicked()
{
    double currentValue = setValueBox->getCurrentValue();
    toggleButton->setText(QString("Toggle\n%1").arg(setValueBox->formatNumber(false, false)));
    setValueBox->setValue(toggleValue);
    toggleValue = currentValue;
}
