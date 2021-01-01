#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include "allgemein.h"

namespace Ui {
class Matrix;
}

class Matrix : public QMainWindow
{
    Q_OBJECT

public:
    explicit Matrix(QWidget *parent = nullptr);
    ~Matrix();

private:
    Ui::Matrix *ui;


private slots:
QVector<QVector<double>> einlesen(int);
void anzeigen();
void change();
void rechnungen();
void erg(QVector<QVector<double>>);
QVector<QVector<double>> mult(QVector<QVector<double>>, QVector<QVector<double>>);

};



#endif // MATRIX_H
