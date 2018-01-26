#include "config_list.h"
#include <QtWidgets>
#include "main.h"
#include "knobbox.h"

ConfigList::ConfigList(const QList<KnobBox *> &_knobList, QWidget *parent)
    : QDialog(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint),
      knobList(_knobList)
{
    setWindowTitle(tr("Configuration sets"));

    itemModel = new QStandardItemModel(this);
    itemView = new QListView;
    itemView->setModel(itemModel);
    itemView->setDragEnabled(false);
    itemView->setAcceptDrops(false);

    loadButton = new QPushButton(tr("&Load"));
    connect(loadButton, &QPushButton::clicked, this, &ConfigList::loadClicked);
    saveButton = new QPushButton(tr("&Save"));
    connect(saveButton, &QPushButton::clicked, this, &ConfigList::saveClicked);
    deleteButton = new QPushButton(tr("&Delete"));
    connect(deleteButton, &QPushButton::clicked, this, &ConfigList::deleteClicked);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(loadButton);
    hbox->addWidget(saveButton);
    hbox->addWidget(deleteButton);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(itemView);
    vbox->addLayout(hbox);

    setLayout(vbox);

    QJsonDocument json = QJsonDocument::fromJson(settings->value("config_sets").toByteArray());
    if (!json.isEmpty()) {
        allKnobsData = json.object().value("knobs").toObject();
        for (QJsonObject::const_iterator i = allKnobsData.constBegin(); i != allKnobsData.constEnd(); ++i) {
            QStandardItem *item = new QStandardItem;
            item->setEditable(false);
            item->setText(i.key());
            itemModel->appendRow(item);
        }
    }
}

void ConfigList::loadClicked()
{
    QModelIndexList sel = itemView->selectionModel()->selectedIndexes();
    if (sel.isEmpty())
        return;
    QStandardItem *item = itemModel->itemFromIndex(sel[0]);
    QString name = item->text();

    QJsonArray knobData = allKnobsData.value(name).toArray();
    for (QJsonArray::const_iterator i = knobData.constBegin(); i != knobData.constEnd(); ++i) {
        int id = (*i).toObject().value("id").toInt();
        QString pv = (*i).toObject().value("pv").toString();
        if ((id >= 0) && (id < knobList.size()))
            knobList[id]->setPV(pv);
    }
    accept();
}

void ConfigList::saveClicked()
{
    bool ok = false;
    QString name = QInputDialog::getText(this, tr("Name"), tr("Please enter a name for the configuration set:"), QLineEdit::Normal, QString(), &ok);
    if ((!ok) || (name.isEmpty()))
        return;

    QJsonArray knobData;
    for (int i = 0; i < knobList.size(); ++i) {
        QJsonObject knobBoxData;
        knobBoxData.insert("id", QJsonValue(i));
        knobBoxData.insert("pv", QJsonValue(knobList[i]->getPV()));
        knobData.append(QJsonObject(knobBoxData));
    }

    allKnobsData.insert(name, QJsonValue(knobData));
    
    QList<QStandardItem *> existingItems = itemModel->findItems(name);
    QStandardItem *item;
    if (existingItems.isEmpty()) {
        item = new QStandardItem;
        item->setEditable(false);
        itemModel->appendRow(item);
    } else
        item = existingItems[0];
    item->setText(name);

    flush();
}

void ConfigList::deleteClicked()
{
    QModelIndexList sel = itemView->selectionModel()->selectedIndexes();
    if (sel.isEmpty())
        return;
    QStandardItem *item = itemModel->itemFromIndex(sel[0]);
    QString name = item->text();
    itemModel->removeRows(sel[0].row(), 1);

    allKnobsData.remove(name);

    flush();
}

void ConfigList::flush()
{
    QJsonObject root;
    root.insert("knobs", QJsonValue(allKnobsData));

    QJsonDocument json;
    json.setObject(root);

    settings->setValue("config_sets", json.toJson(QJsonDocument::Compact));
}

