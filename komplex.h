#ifndef KOMPLEX_H
#define KOMPLEX_H


#include "cmath"
#include <QtDebug>
#include "allgemein.h"
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

    komplex operator*(double d);
    komplex operator/(double d);

    komplex operator+(komplex z);
    komplex operator-(komplex z);
    komplex operator*(komplex z);
    komplex operator/(komplex z);




    //Diese Funktionen sollten nicht benutzt werden
    komplex toKaart(void);
    komplex toPol(void);
};
komplex pow(komplex, double);
komplex pow(double, komplex);
komplex pow(komplex, komplex);
void debug(komplex);


#endif // KOMPLEX_H
