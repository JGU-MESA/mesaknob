#include "pv_list.h"

PvList::PvList(QObject *parent)
    : QObject(parent)
{
    items.append(Pv("cryo:foo-set", "cryo:foo-get", "cryo:foo-output-set", "cryo:foo-output-get", "Foo", "Sinnlose Variable 1"));
    items.append(Pv("cryo:bar", "cryo:bar", "cryo:bar-output-set", "cryo:bar-output-get", "Bar", "Sinnlose Variable 2"));
}

