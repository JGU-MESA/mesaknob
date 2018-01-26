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
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            mainLayout->addWidget(new KnobBox, i, j);

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
}

void MainWindow::recallAll()
{
}

