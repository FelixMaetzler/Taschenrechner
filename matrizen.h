#ifndef MATRIZEN_H
#define MATRIZEN_H

#include <QMainWindow>
#include "allgemein.h"
#include "cmath"

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
void join(matrizen);
void seperate();
int findeZeilemitMax(int, int)const;
void inverse();
bool istUngefaehrGleich(matrizen,int)const;
void zeilenalgorithmus(int, int);
void spaltenalgorithmus(int, int);

void gauss();
int rang()const;
int spur()const;
bool linearAbhaengig(int, int)const;
bool nullZeile(int)const;
void nullZeilenLoeschen();

bool diagonalMatrix()const;
bool obereDreiecksMatrix()const;
bool einheitsMatrix()const;
bool nullMatrix()const;
bool einsMatrix()const;
bool symetrischeMatrix()const;
bool schiefsymetrischeMatrix()const;
bool orthogonnaleMatrix()const;
bool idempotenteMatrix()const;



matrizen operator*(matrizen)const;
matrizen operator*(double)const;
matrizen operator+(matrizen)const;
matrizen operator-(matrizen)const;
};
bool istUngefaehrgleich(double, double, double = pow(10,-9));

#endif // MATRIZEN_H
