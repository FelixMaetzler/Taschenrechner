#ifndef MATRIZEN_H
#define MATRIZEN_H

#include <QMainWindow>
#include "allgemein.h"
#include "cmath"
#include "nullstellenfinder.h"

//Bibliothek zum Rechnen mit Matrizen

class matrizen
{
    QVector<QVector<double>> matrix;

public:
    matrizen();
    matrizen(int, int);
    matrizen(const matrizen*);


    double get_wert(int, int)const;
    void set_wert(double, int, int);
    int spaltenzahl(void)const;
    int zeilenzahl(void)const;
    matrizen get_spalte(int)const;
    void set_spalte(matrizen, int);
    matrizen get_zeile(int)const;
    void set_zeile(matrizen, int);
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
bool gaussform()const;
int rang()const;
int spur()const;
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

double betrag()const;
double betragsquadrat()const;

matrizen hadamard(matrizen)const;
matrizen kronecker(matrizen)const;
int kleinsteDimension()const;
QVector<komplex> eigenwerte()const;
QVector<double> charakteristischesPolynom()const;
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
bool istUngefaehrgleich(double, double, double = pow(10,-9));
double skalarprodukt(matrizen, matrizen);


#endif // MATRIZEN_H
