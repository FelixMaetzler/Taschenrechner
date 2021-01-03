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

    ui->labelError->clear();

    ui->lineMatrixErg->setHidden(true);//nur für Debug auf false. später muss es wieder true

    connect(ui->lineMatrix1, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));
    connect(ui->lineMatrix2, SIGNAL(textChanged(const QString&)), this, SLOT(anzeigen()));
    connect(ui->ButtonChangeAB, SIGNAL(released()), this, SLOT(change()));
    connect(ui->ButtonChangeAErg, SIGNAL(released()), this, SLOT(change()));
    connect(ui->ButtonChangeBErg, SIGNAL(released()), this, SLOT(change()));
    connect(ui->ButtonMult, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonSub, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonInverse1, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonInverse2, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonTransponieren1, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonTransponieren2, SIGNAL(released()), this, SLOT(rechnungen()));

    connect(ui->ButtonLGS, SIGNAL(released()), this, SLOT(rechnungen()));

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
            double wert = Matrix.get_wert(zeilennummer, spaltennummer);
            /*
            if(abs(wert) < pow(10, -6)){
                wert = 0;
            }
            */
            QString text = QString::number(wert);

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
    }
    if(welcheMatrix == Matrix2){
        ui->textMatrix2->setText(text);
    }
    if(welcheMatrix == MatrixErgebnis){
        ui->textMatrixErg->setText(text);
    }

spezielleMatrizen(welcheMatrix, Matrix);
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
            if(abs(wert) < pow(10, -6)){
                wert = 0;
            }
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

void Matrix::rechnungen(){
    ui->labelError->clear();
    matrizen ergebnis;
    matrizen m1 = einlesen(Matrix1);
    matrizen m2 = einlesen(Matrix2);

    if(sender()->objectName().contains("Mult")){
        if(m1.spaltenzahl() != m2.zeilenzahl()){
            ui->labelError->setText("Matrixmultiplikation geht nicht. Falsche Dimension");
        }else{
            ergebnis = m1 * m2;
        }
    }
    if(sender()->objectName().contains("Add")){
        if(m1.zeilenzahl() != m2.zeilenzahl() || m1.spaltenzahl() != m2.spaltenzahl()){
            ui->labelError->setText("Matrixaddition geht nicht. Falsche Dimension");
        }else{
            ergebnis = m1 + m2;
        }
    }
    if(sender()->objectName().contains("Sub")){
        if(m1.zeilenzahl() != m2.zeilenzahl() || m1.spaltenzahl() != m2.spaltenzahl()){
            ui->labelError->setText("Matrixsubtraktion geht nicht. Falsche Dimension");
        }else{
            ergebnis = m1 - m2;
        }
    }
    if(sender()->objectName().contains("Inverse1")){
        matrizen matrix = m1;
        if(!matrix.isSquare()){
            ui->labelError->setText("Matrixsinversion geht nicht. Matrix muss quadratisch sein");
        }else if(matrix.det() == 0){
            ui->labelError->setText("Matrixsinversion geht nicht. Determinante muss != 0 sein");
        }else{
            matrix.inverse();
            ergebnis = matrix;
        }
    }
    if(sender()->objectName().contains("Inverse2")){
        matrizen matrix = m2;
        if(!matrix.isSquare()){
            ui->labelError->setText("Matrixsinversion geht nicht. Matrix muss quadratisch sein");
        }else if(matrix.det() == 0){
            ui->labelError->setText("Matrixsinversion geht nicht. Determinante muss != 0 sein");
        }else{
            matrix.inverse();
            ergebnis = matrix;
        }
    }
    if(sender()->objectName().contains("LGS")){

        if(m1.zeilenzahl() == m1.spaltenzahl() - 1){
            auto spalte = m1.get_spalte(m1.spaltenzahl() - 1);
            m2.resize(m1.zeilenzahl(), 1);
            m2.set_spalte(spalte, 0);
            m1.spalteLoeschen(m1.spaltenzahl() - 1);
        }
        if(!m1.isSquare()){
            ui->labelError->setText("Das LGS muss genausoviele unbekannte wie Gleichungen enthalten");
        }
        if(m2.zeilenzahl() == m1.zeilenzahl() && m2.spaltenzahl() == 1){

        }else if(m2.spaltenzahl() == m1.spaltenzahl() && m2.zeilenzahl() == 1){
            m2.transponieren();
        }else{
            ui->labelError->setText("Der Ergebnisvektor muss genausoviele Zahlen wie Gleichungen enthalten");
        }
        if(m1.det() == 0){
            bool unendlich = true;
            m1.resize(m1.zeilenzahl(), m1.spaltenzahl() + 1);
            m1.set_spalte(m2.get_spalte(0), m1.zeilenzahl());
            m1.gauss();
            QVector<double> letzteZeile = m1.get_zeile(m1.zeilenzahl() - 1);
            foreach(auto x, letzteZeile){
                if(x != 0){
                    unendlich = false;
                    break;
                }
            }
            if(unendlich){
                ui->labelError->setText("Das LGS besitzt unendlich viele Lösungen");
            }else{
                ui->labelError->setText("Das LGS ist nicht lösbar");
            }


        }else{
            m1.inverse();
            ergebnis = m1 * m2;
        }
    }
    if(sender()->objectName().contains("Transponieren1")){

        matrizen matrix = m1;
        matrix.transponieren();
        ergebnis = matrix;

    }
    if(sender()->objectName().contains("Transponieren2")){
        matrizen matrix = m2;
        matrix.transponieren();
        ergebnis = matrix;
    }
    erg(ergebnis);
}
void Matrix::spezielleMatrizen(int welcheMatrix, matrizen matrix){
bool quadratisch = matrix.isSquare();
QString text = "";
text += "Rang: " + QString::number(matrix.rang()) + "\n";
if(quadratisch){
    text += "Determinante: " + QString::number(matrix.det()) + "\n";
    text += "Spur: " + QString::number(matrix.spur()) + "\n";
}
    text += "Spezielle Eigenschaften der Matrix: \n\n";
    if(quadratisch){
        if(matrix.diagonalMatrix()){
            text += "Diagonalmatrix\n";
        }
        if(matrix.einheitsMatrix()){
            text += "Einheitsmatrix\n";
        }

        if(matrix.symetrischeMatrix()){
            text += "symmetische Matrix\n";
        }
        if(matrix.schiefsymetrischeMatrix()){
            text += "schiefsymetrische Matrix\n";
        }
        if(matrix.orthogonnaleMatrix()){
            text += "Orthogonalmatrix\n";
        }
        if(matrix.idempotenteMatrix()){
            text += "idempotente Matrix\n";
        }
    }
    if(matrix.nullMatrix()){
        text += "Nullmatrix";
    }
    if(matrix.einsMatrix()){
        text += "Einsmatrix";
    }
    if(welcheMatrix == Matrix1){
        ui->textEigenschaften1->setText(text);
    }else if(welcheMatrix == Matrix2){
        ui->textEigenschaften2->setText(text);
    }else{
        ui->textEigenschaftenErg->setText(text);
    }
}
