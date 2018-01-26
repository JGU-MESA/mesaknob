#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT
public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
private slots:
	void saveAll();
	void recallAll();
};

#endif // MainWindow_H
