#include "regression.h"
#include "ui_regression.h"

Regression::Regression(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Regression)
{
    ui->setupUi(this);
    ui->lineAusgabe->setReadOnly(true);
    ui->plainPunkte->setReadOnly(true);
    ui->lineAnzeige->setReadOnly(true);
    ui->lineBestimmheitsmass->setReadOnly(true);
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(handeln()));
    connect(ui->ButtonMenu, SIGNAL(released()), this, SLOT(handler()));
    connect(ui->lineEingabe, SIGNAL(textChanged(const QString&)), this, SLOT(handeln()));
}

Regression::~Regression()
{
    delete ui;
}
//TODO https://matheraum.de/forum/Potenzregression/t576753
QVector<double>* Regression::eingabe(){
    auto eingabe = ui->lineEingabe->text();
    auto punkte = eingabe.split(';');
    auto xWerte = new  QVector<double>();
    auto yWerte = new  QVector<double>();
    foreach(auto punkt, punkte){
        auto xWert = punkt.split(',').at(0);
        double y = 0;
        double x = xWert.toDouble();
        if(!x){
            x = 0;
        }
        xWerte->append(x);
        if(punkt.contains(",")){
            auto yWert = punkt.split(',').at(1);
            y = yWert.toDouble();

        }
        yWerte->append(y);
        //Punkte wurden eingelesen

    }
    auto werte = new QVector<double>();
    werte->append(*xWerte);
    werte->append(*yWerte);
    return werte;
}
matrizen lineareRegression(QVector<double>* xWerte, QVector<double>* yWerte, const int Grad){
    if(xWerte->count() != yWerte->count()){
        debug("Punkte machen keinen Sinn");
        return matrizen();
    }
    if(Grad + 1 > xWerte->count()){
        debug("Regression macht keinen Sinn");
        return matrizen();
    }
    matrizen A = matrizen(xWerte->count(), Grad + 1);
    matrizen y = matrizen(yWerte->count(), 1);

    for(int zeile = 0; zeile < A.zeilenzahl(); zeile++){
        for(int spalte = 0; spalte < A.spaltenzahl(); spalte++){
            double wert = pow(xWerte->at(zeile), spalte);
            A.set_wert(wert, zeile, spalte);
        }
    }
    //Matrix A initialisiert
    for(int i = 0; i < y.zeilenzahl(); i++){
        double wert = yWerte->at(i);
        y.set_wert(wert, i, 0);
    }
    //Matrix y initialisiert

    //Least Square Methode x = (A^T * A)^-1 * A^T * y
    matrizen Atransponiert = A;
    Atransponiert.transponieren();
    matrizen erg = Atransponiert * A;
    erg.inverse();
    erg = erg * Atransponiert;
    erg = erg * y;

    return erg;
}
void Regression::handeln(){
    auto liste = eingabe();
    PunkteAnzeigen(liste);
    ui->lineAusgabe->clear();
    auto xWerte = new QVector<double>(*liste);
    auto yWerte = new QVector<double>(*liste);
    xWerte->remove(liste->count()/2, liste->count()/2);
    yWerte->remove(0, liste->count()/2);
    //beide Listen sind jetzt wieder so wie sie sein sollten

    int grad = ui->spinBox->value();
    if(grad + 2 <= xWerte->count() && xWerte->count() == yWerte->count()){
        //dann ist es eine Regression
        ui->lineAnzeige->setText("Regression");
        auto x = lineareRegression(xWerte, yWerte, grad);
        PolynomAnzeigen(x);
        auto R = Bestimmheitsmass(x, xWerte, yWerte);
        ui->lineBestimmheitsmass->setText(QString::number(R));
    }
    if(grad + 1 == xWerte->count() && xWerte->count() == yWerte->count()){
        //dann ist es eine Interpolation
        ui->lineAnzeige->setText("Interpolation");
        auto x = lineareRegression(xWerte, yWerte, grad);
        PolynomAnzeigen(x);
        auto R = Bestimmheitsmass(x, xWerte, yWerte);
        ui->lineBestimmheitsmass->setText(QString::number(R));
    }


}
void Regression::PolynomAnzeigen(matrizen x){
    QString text = "y = ";
    for(int i = x.zeilenzahl() - 1;i >= 0; i--){
        double wert = x.get_wert(i, 0);
        QString zahl = "";
        if(wert > 0 && i != x.zeilenzahl() - 1){
            zahl += "+";
        }
        zahl += QString::number(wert);


        if(i == 0){
            text += zahl;
        }else if(i == 1){
            if(!istUngefaehrgleich(wert, 1)){
                text += zahl;
            }
            text += "x ";
        }else{
            if(wert != 1){
                text += zahl;
            }
            text += "x^" + QString::number(i) + " ";
        }
        ui->lineAusgabe->setText(text);
        //ui->lineAusgabe->setReadOnly(false);
        //ui->lineAusgabe->text() = text;
        //ui->lineAusgabe->setReadOnly(true);
    }
}
void Regression::PunkteAnzeigen(QVector<double>* liste){
    if(liste->count() % 2 != 0){
        debug("Punkte können nicht angezeigt werden");
        return;
    }
    auto xWerte = new QVector<double>(*liste);
    auto yWerte = new QVector<double>(*liste);
    xWerte->remove(liste->count()/2, liste->count()/2);
    yWerte->remove(0, liste->count()/2);
    //beide Listen sind jetzt wieder so wie sie sein sollten
    QString text = "";
    for(int i = 0; i < xWerte->count(); i++){
        text += "(";
        text += QString::number(xWerte->at(i)) + ", ";
        text += QString::number(yWerte->at(i));
        text += ")\n";
    }
    ui->plainPunkte->clear();
    ui->plainPunkte->appendPlainText(text);
}
double Regression::Bestimmheitsmass(matrizen funktion, QVector<double>* xWerte, QVector<double>* yWerte){
    QVector<double>* f = new QVector<double>();
    double mittelwert = 0;
    double SQR = 0;
    double SQT = 0;
    foreach(auto y, *yWerte){
        mittelwert += y;
    }
    mittelwert /= double(yWerte->count());
    for(int i = funktion.zeilenzahl() - 1; i >= 0; i--){
        f->append(funktion.get_wert(i, 0));
    }
   for(int i = 0; i < xWerte->count(); i++){
       double y = yWert(*f, komplex(xWerte->at(i))).get_real();
       double differenz1 = yWerte->at(i) - y;
       differenz1 *= differenz1;
       SQR += differenz1;
       double differenz2 = yWerte->at(i) - mittelwert;
       differenz2 *= differenz2;
       SQT += differenz2;
   }

   double R = 1 - (SQR / SQT);
   return R;
}

void Regression::handler(){//soll das Menu handlen
    auto y = new MainWindow();
    y->show();
    this->close();
}
