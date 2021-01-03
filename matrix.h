#ifndef MATRIX_H
#define MATRIX_H

#include <QMainWindow>
#include "allgemein.h"
#include "matrizen.h"

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

};



#endif // MATRIX_H
