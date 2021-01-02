#ifndef MATRIZEN_H
#define MATRIZEN_H

#include <QMainWindow>
#include "allgemein.h"

class matrizen
{
    QVector<QVector<double>> matrix;

public:
    matrizen();
    matrizen(int, int);

    double get_wert(int, int)const;
    void set_wert(double, int, int);
    int spaltenzahl(void)const;
    int zeilenzahl(void)const;
    QVector<double> get_spalte(int)const;
    void set_spalte(QVector<double>, int);
    QVector<double> get_zeile(int)const;
    void set_zeile(QVector<double>, int);
    void zeilentausch(int, int);
    void spaltentausch(int, int);

    void zeileMult(int, double);
    void zeileMultAdd(int, int, double);
    void print()const;

    bool isSquare()const;
    void toIdentity();
    double det()const;

    void zeileLoeschen(int);
    void spalteLoeschen(int);
    void copy(const matrizen*);
    void transponieren();
    void resize(int, int);
    void nullen();

};

#endif // MATRIZEN_H
