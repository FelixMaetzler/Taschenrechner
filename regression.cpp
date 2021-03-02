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
    connect(ui->radioExponential, SIGNAL(toggled(bool )), this, SLOT(handeln()));
    connect(ui->radioPolynom, SIGNAL(toggled(bool )), this, SLOT(handeln()));
    connect(ui->radioLogarithmus, SIGNAL(toggled(bool )), this, SLOT(handeln()));
    connect(ui->radioPotenz, SIGNAL(toggled(bool )), this, SLOT(handeln()));
    connect(ui->radioExp_beliebig, SIGNAL(toggled(bool )), this, SLOT(handeln()));
    connect(ui->radioLn_beliebig, SIGNAL(toggled(bool )), this, SLOT(handeln()));
    connect(ui->doubleYAchsenabschnitt, SIGNAL(valueChanged(double)), this, SLOT(handeln()));
    connect(ui->radioYAchsenabschnitt, SIGNAL(toggled(bool )), this, SLOT(handeln()));

    ui->Diagramm->addGraph();
    ui->Diagramm->addGraph();
    ui->Diagramm->setInteraction(QCP::iRangeDrag, true);
    ui->Diagramm->setInteraction(QCP::iRangeZoom, true);



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
matrizen lineareRegressionDurchUrsprung(QVector<double>* xWerte, QVector<double>* yWerte, const int Grad){
    if(xWerte->count() != yWerte->count()){
        debug("Punkte machen keinen Sinn");
        return matrizen();
    }
    if(Grad + 1 > xWerte->count()){
        debug("Regression macht keinen Sinn");
        return matrizen();
    }
    matrizen A = matrizen(xWerte->count(), Grad);
    matrizen y = matrizen(yWerte->count(), 1);
    for(int zeile = 0; zeile < A.zeilenzahl(); zeile++){
        for(int spalte = 0; spalte < A.spaltenzahl(); spalte++){
            double wert = pow(xWerte->at(zeile), spalte + 1);
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

matrizen exponentielleRegression(QVector<double>* xWerte, QVector<double>* yWerte){
    auto LNderyWerte = new QVector<double>();
    foreach(double y, *yWerte){
        if(y <= 0){
            debug("Logarithmus geht nur von positiven Zahlen");
            break;
        }
        double ln = log(y);
        LNderyWerte->append(ln);
    }
    auto koeffizienten = lineareRegression(xWerte, LNderyWerte, 1);
    //y = a * e^(bx)
    double a = exp(koeffizienten.get_wert(0,0));
    //double b = koeffizienten.get_wert(1,0);
    koeffizienten.set_wert(a, 0, 0);
    return koeffizienten;
}
matrizen logarithmischeRegression(QVector<double>* xWerte, QVector<double>* yWerte){
    auto LNderxWerte = new QVector<double>();
    foreach(double x, *xWerte){
        if(x <= 0){
            debug("Logarithmus geht nur von positiven Zahlen");
            break;
        }
        double ln = log(x);
        LNderxWerte->append(ln);
    }
    auto koeffizienten = lineareRegression(LNderxWerte, yWerte, 1);
    //y = a * ln(x) + b
    return koeffizienten;
}
matrizen potenzRegression(QVector<double>* xWerte, QVector<double>* yWerte){
    //y = a * x^b
    auto LNderxWerte = new QVector<double>();
    auto LNderyWerte = new QVector<double>();
    foreach(double x, *xWerte){
        if(x <= 0){
            debug("Logarithmus geht nur von positiven Zahlen");
            break;
        }
        double ln = log(x);
        LNderxWerte->append(ln);
    }

    foreach(double y, *yWerte){
        if(y <= 0){
            debug("Logarithmus geht nur von positiven Zahlen");
            break;
        }
        double ln = log(y);
        LNderyWerte->append(ln);
    }
    auto koeffizienten = lineareRegression(LNderxWerte, LNderyWerte, 1);
    //double b = koeffizienten.get_wert(1, 0);
    double a = exp(koeffizienten.get_wert(0 ,0));
    koeffizienten.set_wert(a, 0, 0);
    return koeffizienten;
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

    PunkteEinzeichnen(*xWerte, *yWerte);

    ui->lineAnzeige->clear();
    ui->lineBestimmheitsmass->clear();
    ui->lineAusgabe->clear();

    if(ui->radioPolynom->isChecked()){
        ui->spinBox->show();
        int grad = ui->spinBox->value();
        if(grad + 1 <= xWerte->count() && xWerte->count() == yWerte->count()){

            if(!ui->radioYAchsenabschnitt->isChecked()){
                //ui->lineAnzeige->setText("Regression");
                auto x = lineareRegression(xWerte, yWerte, grad);
                PolynomAnzeigen(x);
                auto R = Bestimmheitsmass(x, xWerte, yWerte);
                ui->lineBestimmheitsmass->setText(QString::number(R));
                return;
            }else{
                if(grad == 0){
                    matrizen x(1, 1);
                    x.set_wert(ui->doubleYAchsenabschnitt->value(), 0, 0);
                    PolynomAnzeigen(x);

                    auto R = Bestimmheitsmass(x, xWerte, yWerte);
                    ui->lineBestimmheitsmass->setText(QString::number(R));
                    return;
                }
                if(grad == xWerte->count() + 1){
                    xWerte->append(0);
                    yWerte->append(ui->doubleYAchsenabschnitt->value());
                    auto x = lineareRegression(xWerte, yWerte, grad);
                    PolynomAnzeigen(x);
                    auto R = Bestimmheitsmass(x, xWerte, yWerte);
                    ui->lineBestimmheitsmass->setText(QString::number(R));
                    return;
                }
                for(int i = 0; i < yWerte->count(); i++){
                    (*yWerte)[i] = yWerte->at(i) - ui->doubleYAchsenabschnitt->value();
                }
                auto x = lineareRegressionDurchUrsprung(xWerte, yWerte, grad);
                for(int i = 0; i < yWerte->count(); i++){
                    (*yWerte)[i] = yWerte->at(i) + ui->doubleYAchsenabschnitt->value();
                }
                matrizen neu(x.zeilenzahl() + 1, 1);
                double yAbschnitt = ui->doubleYAchsenabschnitt->value();
                neu.set_wert(yAbschnitt, 0, 0);
                for(int i = 1; i < neu.zeilenzahl(); i++){
                    neu.set_wert(x.get_wert(i - 1, 0), i, 0);
                }
                PolynomAnzeigen(neu);
                auto R = Bestimmheitsmass(neu, xWerte, yWerte);
                ui->lineBestimmheitsmass->setText(QString::number(R));
                return;

            }
        }

    }else if(ui->radioExponential->isChecked()){
        ui->spinBox->hide();
        if(xWerte->count() > 1 && xWerte->count() == yWerte->count()){
            auto LNyWerte = new QVector<double>();
            foreach(double y, *yWerte){
                if(y <= 0){
                    ui->lineAnzeige->setText("mindestens ein Y Wert ist nicht positiv");
                    return;
                }
                LNyWerte->append(log(y));
            }
            auto exFunktion = exponentielleRegression(xWerte, yWerte);
            matrizen lineareFunktion(2, 1);
            lineareFunktion.set_wert(log(exFunktion.get_wert(0, 0)), 0, 0);
            lineareFunktion.set_wert(exFunktion.get_wert(1, 0), 1, 0);
            double R = Bestimmheitsmass(lineareFunktion, xWerte, LNyWerte);
            ui->lineBestimmheitsmass->setText("R^2 = " + QString::number(R));
            ExponentialAnzeigen(exFunktion.get_wert(0, 0), exFunktion.get_wert(1, 0));
        }else{
            ui->lineAnzeige->setText("zu wenig Punkte");
        }
    }else if(ui->radioLogarithmus->isChecked()){
        ui->spinBox->hide();
        if(xWerte->count() > 1 && xWerte->count() == yWerte->count()){
            auto LNxWerte = new QVector<double>();
            foreach(double x, *xWerte){
                if(x <= 0){
                    ui->lineAnzeige->setText("mindestens ein X Wert ist nicht positiv");
                    return;
                }
                LNxWerte->append(log(x));
            }
            auto lnFunktion = logarithmischeRegression(xWerte, yWerte);
            double R = Bestimmheitsmass(lnFunktion, LNxWerte, yWerte);
            ui->lineBestimmheitsmass->setText("R^2 = " + QString::number(R));
            LogarithmischAnzeigen(lnFunktion.get_wert(1, 0), lnFunktion.get_wert(0, 0));
        }else{
            ui->lineAnzeige->setText("zu wenig Punkte");
        }

    }else if(ui->radioPotenz->isChecked()){
        ui->spinBox->hide();
        if(xWerte->count() > 1 && xWerte->count() == yWerte->count()){
            auto LNxWerte = new QVector<double>();
            auto LNyWerte = new QVector<double>();
            foreach(double x, *xWerte){
                if(x <= 0){
                    ui->lineAnzeige->setText("mindestens ein X Wert ist nicht positiv");
                    return;
                }
                LNxWerte->append(log(x));
            }

            foreach(double y, *yWerte){
                if(y <= 0){
                    ui->lineAnzeige->setText("mindestens ein Y Wert ist nicht positiv");
                    return;
                }
                LNyWerte->append(log(y));
            }

            auto potenzfunktion = potenzRegression(xWerte, yWerte);
            matrizen lineareFunktion(2, 1);
            double a = potenzfunktion.get_wert(0, 0);
            double b = potenzfunktion.get_wert(1, 0);
            lineareFunktion.set_wert(log(a), 0, 0);
            lineareFunktion.set_wert(b, 1, 0);
            double R = Bestimmheitsmass(lineareFunktion, LNxWerte, LNyWerte);
            ui->lineBestimmheitsmass->setText("R^2 = " + QString::number(R));
            PotenzAnzeigen(potenzfunktion.get_wert(0, 0), potenzfunktion.get_wert(1, 0));
        }else{
            ui->lineAnzeige->setText("zu wenig Punkte");
        }
    }else if(ui->radioExp_beliebig->isChecked()){
        ui->spinBox->hide();
        const QString zahl = ui->lineBasis->text();
        const double basis = zahl.toDouble();
        if(basis <= 0){
            ui->lineAnzeige->setText("Basis muss positiv sein");
            return;
        }
        if(xWerte->count() > 1 && xWerte->count() == yWerte->count()){
            auto LNyWerte = new QVector<double>();
            foreach(double y, *yWerte){
                if(y <= 0){
                    ui->lineAnzeige->setText("mindestens ein Y Wert ist nicht positiv");
                    return;
                }
                LNyWerte->append(log(y));
            }
            auto exFunktion = exponentielleRegression(xWerte, yWerte);
            matrizen lineareFunktion(2, 1);
            lineareFunktion.set_wert(log(exFunktion.get_wert(0, 0)), 0, 0);
            lineareFunktion.set_wert(exFunktion.get_wert(1, 0), 1, 0);
            double R = Bestimmheitsmass(lineareFunktion, xWerte, LNyWerte);
            ui->lineBestimmheitsmass->setText("R^2 = " + QString::number(R));
            ExponentialAnzeigen(exFunktion.get_wert(0, 0), exFunktion.get_wert(1, 0), basis);
        }else{
            ui->lineAnzeige->setText("zu wenig Punkte");
        }

    }else if(ui->radioLn_beliebig){
        ui->spinBox->hide();
        const QString zahl = ui->lineBasis->text();
        const double basis = zahl.toDouble();
        if(basis <= 0){
            ui->lineAnzeige->setText("Basis muss positiv sein");
            return;
        }
        if(xWerte->count() > 1 && xWerte->count() == yWerte->count()){
            auto LNxWerte = new QVector<double>();
            foreach(double x, *xWerte){
                if(x <= 0){
                    ui->lineAnzeige->setText("mindestens ein X Wert ist nicht positiv");
                    return;
                }
                LNxWerte->append(log(x));
            }
            auto lnFunktion = logarithmischeRegression(xWerte, yWerte);
            double R = Bestimmheitsmass(lnFunktion, LNxWerte, yWerte);
            ui->lineBestimmheitsmass->setText("R^2 = " + QString::number(R));
            LogarithmischAnzeigen(lnFunktion.get_wert(1, 0), lnFunktion.get_wert(0, 0), basis);
        }else{
            ui->lineAnzeige->setText("zu wenig Punkte");
        }

    }
}
void Regression::PolynomAnzeigen(matrizen x){
    QVector<double> monome;
    for(int i = x.zeilenzahl()-1; i >= 0; i--){
        monome.append(x.get_wert(i, 0));
    }
    PolynomAnzeigen(monome);

    QString text = "y = ";
    for(int i = x.zeilenzahl() - 1;i >= 0; i--){
        double wert = x.get_wert(i, 0);
        QString zahl = "";
        if(wert >= 0 && i != x.zeilenzahl() - 1){
            if(wert != 0){
                zahl += "+";
            }
        }
        if(wert != 0){
            zahl += QString::number(wert);
        }

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
void Regression::ExponentialAnzeigen(double a, double b){
    QString text = "";
    text += QString::number(a) + " * ";
    text += "exp(";
    text += QString::number(b) + " * x)";
    ui->lineAusgabe->setText(text);
}
void Regression::ExponentialAnzeigen(double a, double b, double basis){
    b = b / log(basis);
    QString text = "";
    text += QString::number(a) + " * ";
    text += QString::number(basis) + "^(";
    text += QString::number(b) + " * x)";
    ui->lineAusgabe->setText(text);
}
void Regression::LogarithmischAnzeigen(double a, double b){
    //y = a * ln(x) + b
    QString text = "";
    text += QString::number(a) + " * ";
    text += "ln(x) ";
    if(b >= 0){
        text += "+ ";
    }
    text += QString::number(b);
    ui->lineAusgabe->setText(text);
}
void Regression::LogarithmischAnzeigen(double a, double b, double basis){
    //y = a * log_basis(x) + b
    a = a * log(basis);
    QString text = "";
    text += QString::number(a) + " * ";
    text += "log_(" + QString::number(basis) + ")";
    text += "(x) ";
    if(b >= 0){
        text += "+ ";
    }
    text += QString::number(b);
    ui->lineAusgabe->setText(text);
}
void Regression::PotenzAnzeigen(double a, double b){
    //y = a * x^b
    QString text = "";
    text += QString::number(a) + " * x^";
    text += QString::number(b);
    ui->lineAusgabe->setText(text);
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
void Regression::PunkteEinzeichnen(QVector<double> xWerte, QVector<double> yWerte){


    ui->Diagramm->graph(0)->setLineStyle(QCPGraph::lsNone);//keine Linie
    ui->Diagramm->graph(0)->setScatterStyle(QCPScatterStyle::ssCross);//Kreuze an den Punkten
    ui->Diagramm->graph(0)->setData(xWerte, yWerte);



    ui->Diagramm->replot();
}
void Regression::PolynomAnzeigen(QVector<double> polynom){
    auto xAchse = ui->Diagramm->xAxis->range();

    double Xcenter = xAchse.center();
    double Xrange = xAchse.size();


    double XlowerBound = Xcenter - (Xrange * 0.5);
    double XupperBound = Xcenter + (Xrange * 0.5);


    double Schrittweite = Xrange / 100;
    QVector<double> xWerte;
    QVector<double> yWerte;
    for(double i = XlowerBound; i <= XupperBound; i += Schrittweite){
        double y = yWert(polynom, i);
        xWerte.append(i);
        yWerte.append(y);
    }
    ui->Diagramm->graph(1)->setData(xWerte, yWerte);
    ui->Diagramm->replot();
}



