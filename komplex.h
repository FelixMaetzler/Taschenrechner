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
    void runden(int nachkommastellen = 9);

    komplex operator*(double);
    komplex operator/(double);

    komplex operator+(komplex)const;
    komplex operator-(komplex)const;
    komplex operator*(komplex)const;
    komplex operator/(komplex)const;

    bool operator==(komplex);
    bool operator!=(komplex);

    QString toQstring(void)const;




    //Diese Funktionen sollten nicht benutzt werden
    komplex toKaart(void);
    komplex toPol(void);
};
komplex pow(komplex, double);
komplex pow(double, komplex);
komplex pow(komplex, komplex);
void debug(komplex);


#endif // KOMPLEX_H
