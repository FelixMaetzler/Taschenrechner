#ifndef ALLGEMEIN_H
#define ALLGEMEIN_H

#include <QMainWindow>
#include <QtDebug>
#include <QMainWindow>



class allgemein
{
public:
    allgemein();

};

QMenuBar* addmenu(QMenuBar*);


void debug(QString);
void debug(double);
void debug(QVector<double>);
bool istUngefaehrGleich(double, double, double genauigkeit = 1E-9);




#endif // ALLGEMEIN_H
