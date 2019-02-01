#ifndef KNOB_SELECTION_BUTTON_H
#define KNOB_SELECTION_BUTTON_H

#include <QPushButton>

class KnobSelectionButton : public QPushButton {
Q_OBJECT
    public:
        KnobSelectionButton(int _id, QWidget *parent = 0);
        int getId() const { return id; }
        bool getCumulativeSelection() const { return cumulativeSelection; }
    private slots:
        void mousePressEvent(QMouseEvent *e);
        void mouseMoveEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
    private:
        void updateColor(bool checked);
        int id;
        bool cumulativeSelection;
};


#endif
