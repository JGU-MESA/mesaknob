#include "pv_list.h"

PvList::PvList(QObject *parent)
    : QObject(parent)
{
    items.append(Pv("steam:sv:i_set", "steam:sv:i_get", "steam:sv:on_set", "steam:sv:on_get", "steam:sv", "Irgendein Steerer"));
    items.append(Pv("steam:sh:i_set", "steam:sh:i_get", "steam:sh:on_set", "steam:sh:on_get", "steam:sh", "Irgendein Steerer"));
    items.append(Pv("melba_010:so:i_set", "melba_010:so:i_get", "melba_010:so:on_set", "melba_010:so:on_get", "melba_010:so", "Solenoid"));
    items.append(Pv("melba_010:sv:i_set", "melba_010:sv:i_get", "melba_010:sv:on_set", "melba_010:sv:on_get", "melba_010:sv", "Irgendein Steerer"));
    items.append(Pv("melba_010:sh:i_set", "melba_010:sh:i_get", "melba_010:sh:on_set", "melba_010:sh:on_get", "melba_010:sh", "Irgendein Steerer"));
    items.append(Pv("melba_020:sv:i_set", "melba_020:sv:i_get", "melba_020:sv:on_set", "melba_020:sv:on_get", "melba_020:sv", "Irgendein Steerer"));
    items.append(Pv("melba_020:sh:i_set", "melba_020:sh:i_get", "melba_020:sh:on_set", "melba_020:sh:on_get", "melba_020:sh", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_q1:i_set", "melba_020:trip_q1:i_get", "melba_020:trip_q1:on_set", "melba_020:trip_q1:on_get", "melba_020:trip_q1", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_sv1:i_set", "melba_020:trip_sv1:i_get", "melba_020:trip_sv1:on_set", "melba_020:trip_sv1:on_get", "melba_020:trip_sv1", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_sh1:i_set", "melba_020:trip_sh1:i_get", "melba_020:trip_sh1:on_set", "melba_020:trip_sh1:on_get", "melba_020:trip_sh1", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_q2:i_set", "melba_020:trip_q2:i_get", "melba_020:trip_q2:on_set", "melba_020:trip_q2:on_get", "melba_020:trip_q2", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_sv2:i_set", "melba_020:trip_sv2:i_get", "melba_020:trip_sv2:on_set", "melba_020:trip_sv2:on_get", "melba_020:trip_sv2", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_sh2:i_set", "melba_020:trip_sh2:i_get", "melba_020:trip_sh2:on_set", "melba_020:trip_sh2:on_get", "melba_020:trip_sh2", "Irgendein Steerer"));
    items.append(Pv("melba_020:trip_q3:i_set", "melba_020:trip_q3:i_get", "melba_020:trip_q3:on_set", "melba_020:trip_q3:on_get", "melba_020:trip_q3", "Irgendein Steerer"));
    items.append(Pv("melba_030:sv:i_set", "melba_030:sv:i_get", "melba_030:sv:on_set", "melba_030:sv:on_get", "melba_030:sv", "Irgendein Steerer"));
    items.append(Pv("melba_030:sh:i_set", "melba_030:sh:i_get", "melba_030:sh:on_set", "melba_030:sh:on_get", "melba_030:sh", "Irgendein Steerer"));
    items.append(Pv("melba_030:a:i_set", "melba_030:a:i_get", "melba_030:a:on_set", "melba_030:a:on_get", "melba_030:a", "Alphamagnet"));
    items.append(Pv("melba_030:trip_q1:i_set", "melba_030:trip_q1:i_get", "melba_030:trip_q1:on_set", "melba_030:trip_q1:on_get", "melba_030:trip_q1", "Irgendein Steerer"));
    items.append(Pv("melba_030:trip_sv1:i_set", "melba_030:trip_sv1:i_get", "melba_030:trip_sv1:on_set", "melba_030:trip_sv1:on_get", "melba_030:trip_sv1", "Irgendein Steerer"));
    items.append(Pv("melba_030:trip_sh1:i_set", "melba_030:trip_sh1:i_get", "melba_030:trip_sh1:on_set", "melba_030:trip_sh1:on_get", "melba_030:trip_sh1", "Irgendein Steerer"));
    items.append(Pv("melba_030:trip_q2:i_set", "melba_030:trip_q2:i_get", "melba_030:trip_q2:on_set", "melba_030:trip_q2:on_get", "melba_030:trip_q2", "Irgendein Steerer"));
    items.append(Pv("melba_030:trip_sv2:i_set", "melba_030:trip_sv2:i_get", "melba_030:trip_sv2:on_set", "melba_030:trip_sv2:on_get", "melba_030:trip_sv2", "Irgendein Steerer"));
    items.append(Pv("melba_030:trip_sh2:i_set", "melba_030:trip_sh2:i_get", "melba_030:trip_sh2:on_set", "melba_030:trip_sh2:on_get", "melba_030:trip_sh2", "Irgendein Steerer"));
    items.append(Pv("melba_030:trip_q3:i_set", "melba_030:trip_q3:i_get", "melba_030:trip_q3:on_set", "melba_030:trip_q3:on_get", "melba_030:trip_q3", "Irgendein Steerer"));
    items.append(Pv("melba_040:sv:i_set", "melba_040:sv:i_get", "melba_040:sv:on_set", "melba_040:sv:on_get", "melba_040:sv", "Irgendein Steerer"));
    items.append(Pv("melba_040:sh:i_set", "melba_040:sh:i_get", "melba_040:sh:on_set", "melba_040:sh:on_get", "melba_040:sh", "Irgendein Steerer"));
    items.append(Pv("melba_050:sv:i_set", "melba_050:sv:i_get", "melba_050:sv:on_set", "melba_050:sv:on_get", "melba_050:sv", "Irgendein Steerer"));
    items.append(Pv("melba_050:sh:i_set", "melba_050:sh:i_get", "melba_050:sh:on_set", "melba_050:sh:on_get", "melba_050:sh", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_q1:i_set", "melba_050:trip_q1:i_get", "melba_050:trip_q1:on_set", "melba_050:trip_q1:on_get", "melba_050:trip_q1", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_sv1:i_set", "melba_050:trip_sv1:i_get", "melba_050:trip_sv1:on_set", "melba_050:trip_sv1:on_get", "melba_050:trip_sv1", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_sh1:i_set", "melba_050:trip_sh1:i_get", "melba_050:trip_sh1:on_set", "melba_050:trip_sh1:on_get", "melba_050:trip_sh1", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_q2:i_set", "melba_050:trip_q2:i_get", "melba_050:trip_q2:on_set", "melba_050:trip_q2:on_get", "melba_050:trip_q2", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_sv2:i_set", "melba_050:trip_sv2:i_get", "melba_050:trip_sv2:on_set", "melba_050:trip_sv2:on_get", "melba_050:trip_sv2", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_sh2:i_set", "melba_050:trip_sh2:i_get", "melba_050:trip_sh2:on_set", "melba_050:trip_sh2:on_get", "melba_050:trip_sh2", "Irgendein Steerer"));
    items.append(Pv("melba_050:trip_q3:i_set", "melba_050:trip_q3:i_get", "melba_050:trip_q3:on_set", "melba_050:trip_q3:on_get", "melba_050:trip_q3", "Irgendein Steerer"));
    items.append(Pv("melba_060:sv:i_set", "melba_060:sv:i_get", "melba_060:sv:on_set", "melba_060:sv:on_get", "melba_060:sv", "Irgendein Steerer"));
    items.append(Pv("melba_060:sh:i_set", "melba_060:sh:i_get", "melba_060:sh:on_set", "melba_060:sh:on_get", "melba_060:sh", "Irgendein Steerer"));
}
