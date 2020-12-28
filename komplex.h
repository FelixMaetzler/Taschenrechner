#ifndef KOMPLEX_H
#define KOMPLEX_H


#include "math.h"
#include "allgemein.h"
class komplex
{
    double real;
    double imag;
public:
    komplex();
    komplex(double, double);
    double get_real(void) const;
    double get_imag(void) const;
    void set_real(double);
    void set_imag(double);

    double betrag(void) const;
    double winkel(void) const;

    komplex operator*(double d);
    komplex operator/(double d);
    komplex operator^(double d);

    komplex operator+(komplex z);
    komplex operator-(komplex z);
    komplex operator*(komplex z);
    komplex operator/(komplex z);


private:
    //existiert nur für die Berechnungen
    //deshalb auch Privat
    komplex toKaart(void);
    komplex toPol(void);
};

#endif // KOMPLEX_H
