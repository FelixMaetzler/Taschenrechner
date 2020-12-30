#ifndef NULLSTELLENFINDER_H
#define NULLSTELLENFINDER_H

#include <QMainWindow>
#include "komplex.h"

namespace Ui {
class Nullstellenfinder;
}

class Nullstellenfinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit Nullstellenfinder(QWidget *parent = nullptr);
    ~Nullstellenfinder();

private:
    Ui::Nullstellenfinder *ui;

private slots:
    void berechnen();

};
QVector<komplex> linear(QVector<double>);
QVector<komplex> pqFormel(QVector<double>);
QVector<komplex> cardano(QVector<double>);
QVector<komplex> numerisch(QVector<double>);
komplex yWert(QVector<double>, komplex);//rechnet den yWert eines Polynoms an einer bestimmten Stelle aus
komplex appAusrechnen(QVector<double>, QVector<komplex>, int);//berechnet die Nullstelle der nächsten Iteration
QVector<komplex> PolynomHandler(QVector<double>);//einfach ein polynom übergeben und er spuckt die Nullstellen aus
#endif // NULLSTELLENFINDER_H
