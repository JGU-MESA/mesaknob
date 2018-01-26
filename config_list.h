#ifndef _CONFIG_LIST_H
#define _CONFIG_LIST_H

#include <QDialog>
#include <QList>
#include <QJsonObject>

class QPushButton;
class QStandardItemModel;
class QListView;
class KnobBox;

class ConfigList : public QDialog {
	Q_OBJECT
protected:
	QStandardItemModel *itemModel;
	QListView *itemView;
	void loadClicked();
	void saveClicked();
	void deleteClicked();
	void flush();
	const QList<KnobBox *> &knobList;
private:
	QJsonObject allKnobsData;
	QPushButton *loadButton;
	QPushButton *saveButton;
	QPushButton *deleteButton;
public:
	ConfigList(const QList<KnobBox *> &_knobList, QWidget *parent = 0);
};

#endif
