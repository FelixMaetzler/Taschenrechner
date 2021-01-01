#include "matrix.h"
#include "ui_matrix.h"


enum{MatrixErgebnis, Matrix1, Matrix2};


Matrix::Matrix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
    ui->textMatrix1->setReadOnly(false);
    ui->textMatrix2->setReadOnly(true);

    connect(ui->lineMatrix1, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));
    connect(ui->lineMatrix2, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));
}

Matrix::~Matrix()
{
    delete ui;
}


QVector<QVector<double>> Matrix::einlesen(int welcheMatrix){
    QVector<QVector<double>> Matrix;//Spalten innerhalb der Zeilen
    QString string;
    if(welcheMatrix == Matrix1){
        string = ui->lineMatrix1->text();
    }
    if(welcheMatrix == Matrix2){
        string = ui->lineMatrix2->text();
    }

    auto zeilen = string.split(';');
    int anzahl_spalten = zeilen.at(0).split(',').count();
    /*
    foreach(QString x, zeilen){
        if(x.split(',').count() != anzahl_spalten){
            // Matrix ungültig. Sie hat nicht jede Zeile die gleiche Spaltenzahl
            //Hier muss noch eine Fehlermeldung ausgegeben werden
            return Matrix;
        }
    }
    */
    foreach(QString x, zeilen){
        if(anzahl_spalten < x.split(',').count()){
            anzahl_spalten = x.split(',').count();
        }
    }
    foreach(QString x, zeilen){
        x = "";//nur damit die warnung weg geht
        Matrix.append(QVector<double>(anzahl_spalten));
    }//Matrix ist initialisiert
    for(int zeilennummer = 0; zeilennummer < Matrix.count(); zeilennummer++){
        auto spalte = zeilen.at(zeilennummer).split(',');
        while(spalte.count() != anzahl_spalten){
            spalte.append("");
        }
        for(int spaltennummer = 0; spaltennummer < anzahl_spalten; spaltennummer++){
            QString aktueller_wert = spalte.at(spaltennummer);
            double wert;
            if(aktueller_wert == ""){
                aktueller_wert = "0";
            }
            wert = aktueller_wert.toDouble();

            Matrix[zeilennummer][spaltennummer] = wert;
        }
    }

    return Matrix;
}
void Matrix::anzeigen(){
    int welcheMatrix = -1;
    if(sender()->objectName().contains("1")){
        welcheMatrix = Matrix1;
    }
    if(sender()->objectName().contains("2")){
        welcheMatrix = Matrix2;
    }
    auto Matrix = einlesen(welcheMatrix);
    QString text = "";
    int max_zeichenlaenge = 0;
    for(int zeilennummer = 0; zeilennummer < Matrix.count(); zeilennummer++){
        for(int spaltennummer = 0; spaltennummer < Matrix.at(0).count(); spaltennummer++){
            QString text = QString::number(Matrix.at(zeilennummer).at(spaltennummer));

            if(text.size() > max_zeichenlaenge){
                max_zeichenlaenge = text.size();
            }
        }
    }


    for(int zeilennummer = 0; zeilennummer < Matrix.count(); zeilennummer++){
        QString zeile = "";
        text += "\n";
        for(int spaltennummer = 0; spaltennummer < Matrix.at(0).count(); spaltennummer++){
            QString zahl = QString::number(Matrix.at(zeilennummer).at(spaltennummer));
            while(zahl.size() < max_zeichenlaenge){
                //zahl += " ";

                zahl += " ";
            }
            zeile += zahl + " ";
        }

        text += zeile;

    }
    if(welcheMatrix == Matrix1){
        ui->textMatrix1->setText(text);
    }
    if(welcheMatrix == Matrix2){
        ui->textMatrix2->setText(text);
    }

}
