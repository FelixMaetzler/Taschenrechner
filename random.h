#ifndef RANDOM_H
#define RANDOM_H

#include <QMainWindow>
#include "cmath"
#include "allgemein.h"
#include "mainwindow.h"
namespace Ui {
class random;
}

class random : public QMainWindow
{
    Q_OBJECT

public:
    explicit random(QWidget *parent = nullptr);
    ~random();

private:
    Ui::random *ui;

private slots:
void erneuern();
void handler();
};

QVector<long long> primFaktorZerlegung(long long);
long long ggT(QVector<long long>);
long long kgV(QVector<long long>);
bool istEnthalten(QVector<long long>, long long);
QVector<QVector<long long>> sortieren(QVector<QVector<long long>>);
int anzahlEnthalten(QVector<long long>, long long);
#endif // RANDOM_H
