#include "allgemein.h"

allgemein::allgemein()
{

}

QMenuBar* addmenu(QMenuBar* menubar){

    return menubar;
}


void debug(QString fehler){
    qDebug()<<fehler;
}
