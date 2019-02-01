#include "knob_selection_button.h"
#include <QMouseEvent>
#include <QDebug>

KnobSelectionButton::KnobSelectionButton(int _id, QWidget *parent)
    : QPushButton(QString::number(_id), parent),
      id(_id),
      cumulativeSelection(false)
{
    setCheckable(true);
    updateColor(false);
    connect(this, &QPushButton::toggled, this, &KnobSelectionButton::updateColor);
}

void KnobSelectionButton::updateColor(bool checked)
{
    QColor c;
    switch (id) {
        case 0: c = checked ? QColor(255, 0, 0) : QColor(255, 230, 230); break;
        case 1: c = checked ? QColor(0, 255, 0) : QColor(230, 255, 230); break;
        case 2: c = checked ? QColor(0, 0, 255) : QColor(230, 230, 255); break;
        case 3: c = checked ? QColor(255, 255, 0) : QColor(255, 255, 230); break;
        default: c = Qt::white;
    }
    
    QPalette p = palette();
    p.setColor(QPalette::Active, QPalette::Button, c);
    p.setColor(QPalette::Inactive, QPalette::Button, c);
    setPalette(p);
}

void KnobSelectionButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        setDown(true);
    } else
        QPushButton::mousePressEvent(e);
}

void KnobSelectionButton::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::RightButton) {
        setDown(isChecked() || rect().contains(e->localPos().toPoint()));
    }
    QPushButton::mouseMoveEvent(e);
}

void KnobSelectionButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        if (rect().contains(e->localPos().toPoint())) {
            setDown(false);

            // dirty :(
            cumulativeSelection = true;
            setChecked(!isChecked());
            cumulativeSelection = false;
        } else
            setDown(isChecked());
    } else
        QPushButton::mouseReleaseEvent(e);
}
