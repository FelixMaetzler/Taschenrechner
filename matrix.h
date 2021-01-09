#ifndef MATRIX_H
#define MATRIX_H
#include "matrizen.h"
#include <QMainWindow>
#include "allgemein.h"

#include "mainwindow.h"

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
matrizen einlesen(int);
void anzeigen();
void change();
void rechnungen();
void erg(matrizen);
void spezielleMatrizen(int, matrizen);
void handler();
};



#endif // MATRIX_H
