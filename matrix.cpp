#include "matrix.h"
#include "ui_matrix.h"


enum{MatrixErgebnis, Matrix1, Matrix2};


Matrix::Matrix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Matrix)
{
    ui->setupUi(this);
    ui->textMatrix1->setReadOnly(true);
    ui->textMatrix2->setReadOnly(true);

    ui->lineMatrixErg->setHidden(true);//nur für Debug auf false. später muss es wieder true

    connect(ui->lineMatrix1, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));
    connect(ui->lineMatrix2, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));
    connect(ui->ButtonChangeAB, SIGNAL(released()), this, SLOT(change()));
    connect(ui->ButtonChangeAErg, SIGNAL(released()), this, SLOT(change()));
    connect(ui->ButtonChangeBErg, SIGNAL(released()), this, SLOT(change()));
    connect(ui->ButtonMult, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->lineMatrixErg, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));


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
    if(welcheMatrix == MatrixErgebnis){
        string = ui->lineMatrixErg->text();
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
    if(sender()->objectName().contains("Erg")){
        welcheMatrix = MatrixErgebnis;
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

        for(int spaltennummer = 0; spaltennummer < Matrix.at(0).count(); spaltennummer++){
            QString zahl = QString::number(Matrix.at(zeilennummer).at(spaltennummer));
            int differenz = max_zeichenlaenge - zahl.size();
            for(int i = 0; i < differenz; i++){
                zahl += "  ";
            }
            zahl += "  ";
            zeile += zahl;
        }
        text += zeile;
        text += "\n";
    }
    if(welcheMatrix == Matrix1){
        ui->textMatrix1->setText(text);
        //ui->textMatrix1->setPlainText(text);

    }
    if(welcheMatrix == Matrix2){
        ui->textMatrix2->setText(text);
    }
    if(welcheMatrix == MatrixErgebnis){
        ui->textMatrixErg->setText(text);
    }

}
void Matrix::change(){
    if(sender()->objectName().contains("AB")){
        QString matrix1 = ui->lineMatrix1->text();
        QString matrix2 = ui->lineMatrix2->text();
        ui->lineMatrix1->setText(matrix2);
        ui->lineMatrix2->setText(matrix1);
    }
    if(sender()->objectName().contains("AErg")){
        ui->lineMatrix1->setText(ui->lineMatrixErg->text());
    }
    if(sender()->objectName().contains("BErg")){
        ui->lineMatrix2->setText(ui->lineMatrixErg->text());
    }
}
void Matrix::erg(QVector<QVector<double>> matrix){
    QString text = "";

    for(int zeilennummer = 0; zeilennummer < matrix.count(); zeilennummer++){
        for(int spaltennummer = 0; spaltennummer < matrix.at(0).count(); spaltennummer++){
            double wert = matrix.at(zeilennummer).at(spaltennummer);
            QString val = QString::number(wert);
            text += val + " ";
            if(spaltennummer != matrix.at(0).count() - 1){
                text += ",";
            }
        }
        if(zeilennummer != matrix.count() - 1){
            text += ";";
        }
    }
    ui->lineMatrixErg->setReadOnly(false);
    ui->lineMatrixErg->setText(text);
    ui->lineMatrixErg->setReadOnly(true);
    return;
}
QVector<QVector<double>> Matrix::mult(QVector<QVector<double>> m1, QVector<QVector<double>>m2){
    QVector<QVector<double>> erg;
    if(m1.at(0).count() != m2.count()){
        //kann nicht durchgeführt werden
        return erg;
    }
    int iterationen = m2.count();
    int zeilenzahl = m1.count();
    int spaltenzahl = m2.at(0).count();
    QVector<double> spalte;
    for(int i = 0; i < spaltenzahl; i++){
        spalte.append(0);
    }
    for(int i = 0; i < zeilenzahl; i++){
        erg.append(spalte);
    }
    //erg Matrix hat jetzt die richtigen Dimensionen
    for(int zeilennummer = 0; zeilennummer < erg.count(); zeilennummer++){
        for(int spaltennummer = 0; spaltennummer < erg.at(0).count(); spaltennummer++){
       double wert = 0;
       for(int i = 0; i < iterationen; i++){
           wert += m1.at(zeilennummer).at(i) * m2.at(i).at(spaltennummer);
       }
       erg[zeilennummer][spaltennummer] = wert;
        }
    }
    return erg;
}
void Matrix::rechnungen(){
QVector<QVector<double>> ergebnis;
QVector<QVector<double>> m1 = einlesen(Matrix1);
QVector<QVector<double>> m2 = einlesen(Matrix2);

    if(sender()->objectName().contains("Mult")){
    ergebnis = mult(m1, m2);
}
    erg(ergebnis);
}
