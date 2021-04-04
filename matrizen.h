#ifndef MATRIZEN_H
#define MATRIZEN_H

#include <QMainWindow>
#include "allgemein.h"
#include "cmath"
//#include "nullstellenfinder.h"
#include "nullstelle.h"
#include "komplex.h"
//Bibliothek zum Rechnen mit Matrizen

class matrizen
{
    QVector<QVector<komplex>> matrix;

public:
    matrizen();
    matrizen(int, int);
    matrizen(const matrizen*);


    komplex get_wert(int, int)const;
    void set_wert(komplex, int, int);
    int spaltenzahl(void)const;
    int zeilenzahl(void)const;
    matrizen get_spalte(int)const;
    void set_spalte(matrizen, int);
    matrizen get_zeile(int)const;
    void set_zeile(matrizen, int);
    void zeilentausch(int, int);
    void spaltentausch(int, int);

    void zeileMult(int, komplex);
    void zeileMultAdd(int, int, komplex);
    void print()const;

    bool isSquare()const;
    void toIdentity();
    komplex det()const;

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
bool istUngefaehrgleich(matrizen, double)const;
void zeilenalgorithmus(int, int);
void spaltenalgorithmus(int, int);

void gauss();
bool gaussform()const;
int rang()const;
komplex spur()const;
bool linearAbhaengig(int, int)const;
bool nullZeile(int)const;
bool nullSpalte(int)const;
void nullZeilenLoeschen();
void nullSpaltenLoeschen();

bool diagonalMatrix()const;
bool obereDreiecksMatrix()const;
bool einheitsMatrix()const;
bool nullMatrix()const;
bool einsMatrix()const;
bool symetrischeMatrix()const;
bool schiefsymetrischeMatrix()const;
bool orthogonnaleMatrix()const;
bool idempotenteMatrix()const;

komplex betrag()const;
komplex betragsquadrat()const;

matrizen hadamard(matrizen)const;
matrizen kronecker(matrizen)const;
int kleinsteDimension()const;
QVector<komplex> eigenwerte()const;
QVector<komplex> charakteristischesPolynom()const;
void Toeplitz();
matrizen R(int)const;
matrizen A(int)const;
matrizen S(int)const;
matrizen q(int)const;
matrizen power(int)const;
matrizen unterbestimmt()const;

matrizen operator*(matrizen)const;
matrizen operator*(double)const;
matrizen operator+(matrizen)const;
matrizen operator-(matrizen)const;
};
//bool istUngefaehrGleich(double, double, double = pow(10,-9));
komplex skalarprodukt(matrizen, matrizen);


#endif // MATRIZEN_H
