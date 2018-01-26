#include <QtWidgets>
#include "mainwindow.h"
#include "knobmanager.h"
#include "knobbox.h"
#include "powermate.h"
#include "main.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (col == 2)
                ++col;
            KnobBox *knobBox = new KnobBox;
            knobBoxes.append(knobBox);
            mainLayout->addWidget(knobBox, row, col);
        }
    }
    QFrame *separator = new QFrame;
    separator->setLineWidth(2);
    separator->setFrameShape(QFrame::VLine);
    mainLayout->addWidget(separator, 0, 2, 4, 1);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    QAction *actSaveAll = new QAction(tr("&Save all"));
    actSaveAll->setShortcut(QKeySequence("Ctrl+S"));
    connect(actSaveAll, &QAction::triggered, this, &MainWindow::saveAll);
    QAction *actRecallAll = new QAction(tr("&Recall all"));
    actRecallAll->setShortcut(QKeySequence("Ctrl+R"));
    connect(actRecallAll, &QAction::triggered, this, &MainWindow::recallAll);
    QAction *actExit = new QAction(tr("E&xit"));
    actExit->setShortcuts(QKeySequence::Quit);
    connect(actExit, &QAction::triggered, this, &QWidget::close);
    
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(actSaveAll);
    fileMenu->addAction(actRecallAll);
    fileMenu->addSeparator();
    fileMenu->addAction(actExit);
}

MainWindow::~MainWindow()
{
}

void MainWindow::saveAll()
{
    for (QList<KnobBox *>::const_iterator i = knobBoxes.cbegin(); i != knobBoxes.cend(); ++i)
        (*i)->saveClicked();
}

void MainWindow::recallAll()
{
    for (QList<KnobBox *>::const_iterator i = knobBoxes.cbegin(); i != knobBoxes.cend(); ++i)
        (*i)->recallClicked();
}

