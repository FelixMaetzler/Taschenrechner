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


matrizen Matrix::einlesen(int welcheMatrix){

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
    /*
    foreach(QString x, zeilen){
        x = "";//nur damit die warnung weg geht
        Matrix.append(QVector<double>(anzahl_spalten));

    }//Matrix ist initialisiert
    */
    matrizen Matrix(zeilen.count(), anzahl_spalten);
    for(int zeilennummer = 0; zeilennummer < Matrix.zeilenzahl(); zeilennummer++){
        auto spalte = zeilen.at(zeilennummer).split(',');
        while(spalte.count() != anzahl_spalten){
            spalte.append("");
        }
        for(int spaltennummer = 0; spaltennummer < Matrix.spaltenzahl(); spaltennummer++){
            QString aktueller_wert = spalte.at(spaltennummer);
            double wert;
            if(aktueller_wert == ""){
                aktueller_wert = "0";
            }
            wert = aktueller_wert.toDouble();

            Matrix.set_wert(wert, zeilennummer, spaltennummer);
        }
    }

    return Matrix;
}
void Matrix::anzeigen(){
    ui->labelError->clear();
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
    for(int zeilennummer = 0; zeilennummer < Matrix.zeilenzahl(); zeilennummer++){
        for(int spaltennummer = 0; spaltennummer < Matrix.spaltenzahl(); spaltennummer++){
            QString text = QString::number(Matrix.get_wert(zeilennummer, spaltennummer));

            if(text.size() > max_zeichenlaenge){
                max_zeichenlaenge = text.size();
            }
        }
    }


    for(int zeilennummer = 0; zeilennummer < Matrix.zeilenzahl(); zeilennummer++){
        QString zeile = "";

        for(int spaltennummer = 0; spaltennummer < Matrix.spaltenzahl(); spaltennummer++){
            QString zahl = QString::number(Matrix.get_wert(zeilennummer, spaltennummer));
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
    ui->labelError->clear();
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
void Matrix::erg(matrizen matrix){
    QString text = "";

    for(int zeilennummer = 0; zeilennummer < matrix.zeilenzahl(); zeilennummer++){
        for(int spaltennummer = 0; spaltennummer < matrix.spaltenzahl(); spaltennummer++){
            double wert = matrix.get_wert(zeilennummer, spaltennummer);
            QString val = QString::number(wert);
            text += val + " ";
            if(spaltennummer != matrix.spaltenzahl() - 1){
                text += ",";
            }
        }
        if(zeilennummer != matrix.zeilenzahl() - 1){
            text += ";";
        }
    }
    ui->lineMatrixErg->setReadOnly(false);
    ui->lineMatrixErg->setText(text);
    ui->lineMatrixErg->setReadOnly(true);
    return;
}
matrizen Matrix::mult(matrizen m1, matrizen m2){
    /*
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
    */
    if(m1.spaltenzahl() != m2.zeilenzahl()){
        ui->labelError->setText("Matrixmultiplikation geht nicht. Falsche Dimension");
        return matrizen();
    }
    return (m1 * m2);
}
void Matrix::rechnungen(){
    ui->labelError->clear();
    matrizen ergebnis;
    matrizen m1 = einlesen(Matrix1);
    matrizen m2 = einlesen(Matrix2);

    if(sender()->objectName().contains("Mult")){
        ergebnis = mult(m1, m2);
    }
    erg(ergebnis);
}
