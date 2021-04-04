#ifndef KOMPLEX_H
#define KOMPLEX_H


#include "cmath"
#include <QtDebug>
#include "allgemein.h"

//Bibliothek zum handlen komplexer Zahlen

class komplex
{
    double real;
    double imag;

public:
    komplex();
    komplex(double, double);
    komplex(double);
    double get_real(void) const;
    double get_imag(void) const;
    void set_real(double);
    void set_imag(double);

    double betrag(void) const;
    double winkel(void) const;
    void runden(int nachkommastellen = 9);



    komplex operator+(komplex)const;
    komplex operator-(komplex)const;
    komplex operator*(komplex)const;
    komplex operator/(komplex)const;





    komplex operator+=(komplex)const;
    komplex operator-=(komplex)const;
    komplex operator*=(komplex)const;
    komplex operator/=(komplex)const;

    bool operator==(komplex)const;
    bool operator!=(komplex)const;


    QString toQstring(void)const;




    //Diese Funktionen sollten nicht benutzt werden
    komplex toKaart(void)const;
    komplex toPol(void)const;
};
komplex pow(komplex, double);
komplex pow(double, komplex);
komplex pow(komplex, komplex);
bool istUngefaehrGleich(komplex, komplex, double genauigkeit = 1E-9);
void debug(komplex);


#endif // KOMPLEX_H
