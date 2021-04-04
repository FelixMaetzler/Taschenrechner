#include "allgemein.h"

allgemein::allgemein()
{

}

QMenuBar* addmenu(QMenuBar* menubar){

    return menubar;
}


void debug(QString fehler){
    qDebug()<<fehler;
    return;
}
void debug(double fehler){
    debug(QString::number(fehler));
    return;
}
void debug(QVector<double> liste){
    QString text = "";
    foreach(auto x, liste){
        text += QString::number(x) + " ";
    }
    debug(text);
}
bool istUngefaehrGleich(double wert1, double wert2, double genauigkeit){
    //vergleicht ob ein Wert gleich dem anderen ist
    //Falls diese durch Rundungen nicht exakt gleich ist
    return (abs(wert1 - wert2) <= genauigkeit);
}
