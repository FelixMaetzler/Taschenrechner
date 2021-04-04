#ifndef NULLSTELLE_H
#define NULLSTELLE_H
#include "komplex.h"
#include "allgemein.h"
class nullstelle
{
public:
    nullstelle();
};
QVector<komplex> linear(QVector<double>);
QVector<komplex> linear(QVector<komplex>);
QVector<komplex> pqFormel(QVector<double>);
QVector<komplex> pqFormel(QVector<komplex>);
QVector<komplex> cardano(QVector<double>);
QVector<komplex> numerisch(QVector<double>);
QVector<komplex> ableiten(QVector<komplex>);
QVector<double> toReal(QVector<komplex>);
QVector<komplex> toKomplex(QVector<double>);
QVector<double> listeReversen(QVector<double>);
QVector<komplex> listeReversen(QVector<komplex>);
QVector<komplex> hornerschema(QVector<komplex>, komplex);
komplex newton(QVector<komplex>, komplex startwert = komplex(1,1));
//bool istUngefaerGleich(double, double, double genauigkeit = pow(10,-9));
//bool istUngefaerGleich(komplex, komplex, double genauigkeit = pow(10,-9));
void newtonNullstellen(QVector<komplex>, QVector<komplex>*);
komplex yWert(QVector<double>, komplex);//rechnet den yWert eines Polynoms an einer bestimmten Stelle aus
komplex yWert(QVector<komplex>, komplex);//rechnet den yWert eines Polynoms an einer bestimmten Stelle aus
double yWert(QVector<double>, double);//rechnet den yWert eines Polynoms an einer bestimmten Stelle aus
komplex appAusrechnen(QVector<double>, QVector<komplex>, int);//berechnet die Nullstelle der nächsten Iteration
QVector<komplex> PolynomHandler(QVector<double>);//einfach ein polynom übergeben und er spuckt die Nullstellen aus
QVector<komplex> PolynomHandler(QVector<komplex>);
#endif // NULLSTELLE_H
