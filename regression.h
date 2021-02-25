#ifndef REGRESSION_H
#define REGRESSION_H

#include <QMainWindow>

#include "mainwindow.h"
#include "allgemein.h"
#include "matrizen.h"
#include "math.h"

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
    void ExponentialAnzeigen(double, double);
    void LogarithmischAnzeigen(double, double);
    void ExponentialAnzeigen(double, double, double);
    void LogarithmischAnzeigen(double, double, double);
    void PotenzAnzeigen(double, double);
    void PunkteAnzeigen(QVector<double>*);
    double Bestimmheitsmass(matrizen, QVector<double>*, QVector<double>*);


};
matrizen lineareRegression(QVector<double>*, QVector<double>*, const int);
matrizen lineareRegressionDurchUrsprung(QVector<double>*, QVector<double>*, const int);
matrizen exponentielleRegression(QVector<double>*, QVector<double>*);
matrizen logarithmischeRegression(QVector<double>*, QVector<double>*);
matrizen potenzRegression(QVector<double>*, QVector<double>*);


#endif // REGRESSION_H
