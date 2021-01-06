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
    connect(ui->ButtonHadamard, SIGNAL(released()), this, SLOT(rechnungen()));
    connect(ui->ButtonKronecker, SIGNAL(released()), this, SLOT(rechnungen()));
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
    //liest eine Matrix ein
    QString string;
    //je nachdem welche Matrix gelesen werden soll
    if(welcheMatrix == Matrix1){
        string = ui->lineMatrix1->text();
    }
    if(welcheMatrix == Matrix2){
        string = ui->lineMatrix2->text();
    }
    if(welcheMatrix == MatrixErgebnis){
        string = ui->lineMatrixErg->text();
    }
    if(string == ""){//falls das Textfeld leer ist
        return matrizen(0,0);//wird eine Matrize mit 0 Zeilen und 0 Spalten zurückgegeben
    }

    auto zeilen = string.split(';');//String wird an dem Semikolon gesplitet. Damit hat man eine Liste an Strings die die einzelnen Zeilen repräsentieren
    //int anzahl_spalten = zeilen.at(0).split(',').count();
    int anzahl_spalten = -INFINITY;//damit jede Zahl größer ist
    /*
    foreach(QString x, zeilen){
        if(x.split(',').count() != anzahl_spalten){
            // Matrix ungültig. Sie hat nicht jede Zeile die gleiche Spaltenzahl
            //Hier muss noch eine Fehlermeldung ausgegeben werden
            return Matrix;
        }
    }
    */
    foreach(QString x, zeilen){//geht durch jede Zeile durch und zählt die Einträge
        if(anzahl_spalten < x.split(',').count()){
            anzahl_spalten = x.split(',').count();
        }
    }//anzahl_spalten besitzt jetzt den Wert der maximalen Spalten
    /*
    foreach(QString x, zeilen){
        x = "";//nur damit die warnung weg geht
        Matrix.append(QVector<double>(anzahl_spalten));

    }//Matrix ist initialisiert
    */
    matrizen Matrix(zeilen.count(), anzahl_spalten);//erstellt eine Matrix mit der richtigen Größe
    for(int zeilennummer = 0; zeilennummer < Matrix.zeilenzahl(); zeilennummer++){
        auto spalte = zeilen.at(zeilennummer).split(',');
        while(spalte.count() != anzahl_spalten){
            spalte.append("");
        }//bringt alle Zeilen auf die gleiche Spaltenzahl
        for(int spaltennummer = 0; spaltennummer < Matrix.spaltenzahl(); spaltennummer++){
            QString aktueller_wert = spalte.at(spaltennummer);
            double wert;
            if(aktueller_wert == ""){//falls ein Element leer ist, wird es mit 0 überschrieben
                aktueller_wert = "0";
            }
            wert = aktueller_wert.toDouble();

            Matrix.set_wert(wert, zeilennummer, spaltennummer);
        }
    }//Matrix ist fertig;

    return Matrix;
}
void Matrix::anzeigen(){
    ui->labelError->clear();
    int welcheMatrix = -1;
    //schaut welche matrix es überhaupt ist
    if(sender()->objectName().contains("1")){
        welcheMatrix = Matrix1;
    }
    if(sender()->objectName().contains("2")){
        welcheMatrix = Matrix2;
    }
    if(sender()->objectName().contains("Erg")){
        welcheMatrix = MatrixErgebnis;
    }

    auto Matrix = einlesen(welcheMatrix);//Matrix wird eingelesen
    if(!(Matrix.zeilenzahl() == 0 && Matrix.spaltenzahl() == 0)){//Wenn die Matrix nicht leer ist

        QString text = "";
        int max_zeichenlaenge = -INFINITY;
        //findet die maximale zeichenlänge, damit nachher die Elemente möglichst schön untereinander sind
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
        }//maximale Zeichenzahl geefunden


        for(int zeilennummer = 0; zeilennummer < Matrix.zeilenzahl(); zeilennummer++){
            QString zeile = "";

            for(int spaltennummer = 0; spaltennummer < Matrix.spaltenzahl(); spaltennummer++){
                QString zahl = QString::number(Matrix.get_wert(zeilennummer, spaltennummer));
                int differenz = max_zeichenlaenge - zahl.size();
                for(int i = 0; i < differenz; i++){
                    zahl += "  ";
                }//füllt die Differenz zwischen der aktuellen zeichenzahl und der maximalen Zeichenzahl mit Leerzeichen auf
                zahl += "  ";
                zeile += zahl;
            }
            //nach jeder Zeile wird ein Zeilenumbruch gemacht
            text += zeile;
            text += "\n";
        }
        //zeigt die Matrix an
        if(welcheMatrix == Matrix1){
            ui->textMatrix1->setText(text);
        }
        if(welcheMatrix == Matrix2){
            ui->textMatrix2->setText(text);
        }
        if(welcheMatrix == MatrixErgebnis){
            ui->textMatrixErg->setText(text);
        }
        //ruft eine Funktion auf, die sich die Eigenschaften der Matrix anschaut
        spezielleMatrizen(welcheMatrix, Matrix);
    }else{//die Matrix ist leer
        //dann wird das entsprechende Feld gelöscht
        if(welcheMatrix == Matrix1){
            ui->textMatrix1->clear();
            ui->textEigenschaften1->clear();
        }
        if(welcheMatrix == Matrix2){
            ui->textMatrix2->clear();
            ui->textEigenschaften2->clear();
        }
        if(welcheMatrix == MatrixErgebnis){
            ui->textMatrixErg->clear();
            ui->textEigenschaftenErg->clear();
        }
    }
}
void Matrix::change(){
    //einer der Tasuchen Buttons wurde gedrückt
    ui->labelError->clear();
    //Je nachdem welcher Gedrückt wurde, werden die entsprechenden Matrizen getauscht
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
    //wandet die Ergebnismatrix in die Schreibweise mit , und ; um
    QString text = "";

    for(int zeilennummer = 0; zeilennummer < matrix.zeilenzahl(); zeilennummer++){
        for(int spaltennummer = 0; spaltennummer < matrix.spaltenzahl(); spaltennummer++){
            double wert = matrix.get_wert(zeilennummer, spaltennummer);
            if(abs(wert) < pow(10, -6)){//rundet kleinere Zahlen als 0.0000001 zu 0
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
    //und schreibt diesen Text in ein unsichtbares Feld
    ui->lineMatrixErg->setReadOnly(false);
    ui->lineMatrixErg->setText(text);
    ui->lineMatrixErg->setReadOnly(true);
    return;
}

void Matrix::rechnungen(){
    //führt jegliche Rechnungen aus
    ui->labelError->clear();
    matrizen ergebnis;
    matrizen m1 = einlesen(Matrix1);
    matrizen m2 = einlesen(Matrix2);

    if(sender()->objectName().contains("Mult")){
        if(m1.spaltenzahl() != m2.zeilenzahl()){//prüft ob eine Multiplikation überhaupt möglich ist
            ui->labelError->setText("Matrixmultiplikation geht nicht. Falsche Dimension");
        }else{
            ergebnis = m1 * m2;
        }
    }
    if(sender()->objectName().contains("Add")){
        if(m1.zeilenzahl() != m2.zeilenzahl() || m1.spaltenzahl() != m2.spaltenzahl()){//prüft ob eine Addition überhaupt möglich ist
            ui->labelError->setText("Matrixaddition geht nicht. Falsche Dimension");
        }else{
            ergebnis = m1 + m2;
        }
    }
    if(sender()->objectName().contains("Sub")){
        if(m1.zeilenzahl() != m2.zeilenzahl() || m1.spaltenzahl() != m2.spaltenzahl()){//Prüft ob eine Substraktion überhaupt möglich ist
            ui->labelError->setText("Matrixsubtraktion geht nicht. Falsche Dimension");
        }else{
            ergebnis = m1 - m2;
        }
    }
    if(sender()->objectName().contains("Inverse1")){
        matrizen matrix = m1;
        if(!matrix.isSquare()){//prüft ob eine Invertierung möglich ist
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
        if(!matrix.isSquare()){//prüft ob eine Invertierung möglich ist
            ui->labelError->setText("Matrixsinversion geht nicht. Matrix muss quadratisch sein");
        }else if(matrix.det() == 0){
            ui->labelError->setText("Matrixsinversion geht nicht. Determinante muss != 0 sein");
        }else{
            matrix.inverse();
            ergebnis = matrix;
        }
    }
    if(sender()->objectName().contains("LGS")){
        /*
        es gibt verschiedene Möglichkeiten ein LGS einzugeben:
        - alles eine Matrix und Ergebnisvektor als letzte Spalte
        - quadratische Matrix ins linke Feld und dann Ergebnisvektor als Zeilen oder Spaltenvektor ins rechte Feld
        OTIMALER FALL: links eine quadratische Matrix und rechts einen Spaltenvektor
        */
        if(m1.zeilenzahl() == m1.spaltenzahl() - 1){//falls ersteres, dann wird es zum optimalen Fall gemacht
            auto spalte = m1.get_spalte(m1.spaltenzahl() - 1);
            m2.resize(m1.zeilenzahl(), 1);
            m2.set_spalte(spalte, 0);
            m1.spalteLoeschen(m1.spaltenzahl() - 1);
        }
        if(m1.isSquare()){//Falls links quadratisch

            if(m2.zeilenzahl() == m1.zeilenzahl() && m2.spaltenzahl() == 1){//Falls rechts ein Spaltenvektor mit der richtigen Dimension ist
                //dann wird nix gemacht weil das der optimale Fall ist
            }else if(m2.spaltenzahl() == m1.spaltenzahl() && m2.zeilenzahl() == 1){//Falls rechts ein Zeilenvektor mit der richtigen Dimenion ist
                m2.transponieren();//dann wird dieser tranponiert
            }else{//und falls nichts davon der fall ist
                //wird eine Fehlermeldung ausgegeben
                ui->labelError->setText("Der Ergebnisvektor muss genausoviele Zahlen wie Gleichungen enthalten");
            }
            if(m1.det() == 0){//falls die Determinante 0 ist, dann ist das LGS nicht eindeutig Lösbar
                //es ist entweder gar nicht lösbar oder es besitzt unendlich Lösungen
                bool unendlich = true;
                m1.resize(m1.zeilenzahl(), m1.spaltenzahl() + 1);
                m1.set_spalte(m2.get_spalte(0), m1.zeilenzahl());
                //links wird rechts als letzte Spalte angehängt
                m1.gauss();//Gauss wird durchgeführt
                //falls die letzte Zeile eine komplette Nullzeile ist, dann gibt es unendlich viele Lösungen
                auto letzteZeile = m1.get_zeile(m1.zeilenzahl() - 1);
                for(int i = 0; i < letzteZeile.spaltenzahl(); i++){
                    double x = letzteZeile.get_wert(0, i);
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


            }else{//falls die Determinante nicht Null ist, dann ist es einfeutig Lösbar
                m1.inverse();//die Lösung wird über die Inverse bestimmt
                ergebnis = m1 * m2;
            }
        }else{
            //ui->labelError->setText("Das LGS muss genausoviele unbekannte wie Gleichungen enthalten");
            if(m1.zeilenzahl() > m1.spaltenzahl()){
                ui->labelError->setText("Das LGS ist überdefiniert. Es hat mehr Gleichungen als Unbekannte");
            }else{
                ui->labelError->setText("Das LGS ist unterdefiniert. Es hat mehr Unbekannte als Gleichungen");
            }
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
    if(sender()->objectName().contains("Hadamard")){
        if(!(m1.zeilenzahl() == m2.zeilenzahl() && m1.spaltenzahl() == m2.spaltenzahl())){
            ui->labelError->setText("Hadamard geht nicht. falsche Dimensionen");
        }else{
            ergebnis = m1.hadamard(m2);
        }
    }
    if(sender()->objectName().contains("Kronecker")){
        ergebnis = m1.kronecker(m2);
    }
    erg(ergebnis);//Ergebnismatix wird in Text konvertiert und angezeigt
}
void Matrix::spezielleMatrizen(int welcheMatrix, matrizen matrix){
    bool quadratisch = matrix.isSquare();//speichert, ob die Matrix quadratisch ist
    QString text = "";
    text += "Rang: " + QString::number(matrix.rang()) + "\n";//berechnet den Rang der Matrix
    if(quadratisch){//wenn sie quadratisch ist, dann
        text += "Determinante: " + QString::number(matrix.det()) + "\n";//wird die Determinante
        text += "Spur: " + QString::number(matrix.spur()) + "\n";//und die Spur berechnet
    }
    text += "Spezielle Eigenschaften der Matrix: \n\n";
    if(quadratisch){//ausßerdem wird die Matrix dann auf folgendes geprüft:
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
