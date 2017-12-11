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
}

MainWindow::~MainWindow()
{
}
