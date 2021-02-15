#ifndef REGRESSION_H
#define REGRESSION_H

#include <QMainWindow>

#include "mainwindow.h"
#include "allgemein.h"
#include "matrizen.h"

namespace Ui {
class Regression;
}

class Regression : public QMainWindow
{
    Q_OBJECT

public:
    explicit Regression(QWidget *parent = nullptr);
    ~Regression();

private:
    Ui::Regression *ui;


private slots:
    void handler();
    QVector<double>* eingabe();
    void handeln();
    void PolynomAnzeigen(matrizen);
    void PunkteAnzeigen(QVector<double>*);
    double Bestimmheitsmass(matrizen, QVector<double>*, QVector<double>*);

};
matrizen lineareRegression(QVector<double>*, QVector<double>*, const int);



#endif // REGRESSION_H
