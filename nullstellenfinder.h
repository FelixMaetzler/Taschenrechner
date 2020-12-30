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

};
QVector<komplex> linear(QVector<double>);
QVector<komplex> abcFormel(QVector<double>);
QVector<komplex> cardano(QVector<double>);
QVector<komplex> numerisch(QVector<double>);
komplex yWert(QVector<double>, komplex);//rechnet den yWert eines Polynoms an einer bestimmten Stelle aus
komplex appAusrechnen(QVector<double>, QVector<komplex>, int);//berechnet die Nullstelle der nächsten Iteration
#endif // NULLSTELLENFINDER_H
