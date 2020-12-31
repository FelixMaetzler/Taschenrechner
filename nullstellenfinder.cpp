#include "nullstellenfinder.h"
#include "ui_nullstellenfinder.h"

Nullstellenfinder::Nullstellenfinder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nullstellenfinder)
{
    ui->setupUi(this);

    ui->label_Equation->clear();
    connect(ui->ButtonBerechnen, SIGNAL(released()), this, SLOT(berechnen()));
}

Nullstellenfinder::~Nullstellenfinder()
{
    delete ui;
}
QVector<komplex> linear(QVector<double> inputs){
    double erg = -inputs.at(1)/inputs.at(0);
    QVector<komplex> outputs;
    outputs.append(komplex(erg));
    return outputs;
}
QVector<komplex> pqFormel(QVector<double> inputs){
    QVector<komplex> outputs;
    komplex a(inputs.at(0));
    komplex b(inputs.at(1));
    komplex c(inputs.at(2));
    komplex p(b/a);
    komplex q(c/a);
    komplex x1 = (p/-2.0)+pow(pow(p/2.0,2) - q, 0.5);
    komplex x2 = (p/-2.0)-pow(pow(p/2.0,2) - q, 0.5);
    outputs.append(x1);
    outputs.append(x2);
    return outputs;
}
QVector<komplex> cardano(QVector<double> inputs){
    //https://matheplanet.com/default3.html?call=article.php?sid=483&ref=https%3A%2F%2Fwww.google.com%2F
    QVector<komplex> outputs;
    double a = inputs.at(0);
    double b = inputs.at(1);
    double c = inputs.at(2);
    double d = inputs.at(3);
    double r = b/a;
    double s = c/a;
    double t = d/a;
    double p = s - pow(r, 2.0) / 3.0;
    double q = pow(r, 3.0) * (2.0/27.0) - (s * r) / 3.0 + t;
    double D = pow(q/2.0, 2.0) + pow(p/3.0, 3.0);
    if(D<0){
        double phi = acos((-q)/(2.0*pow(-p/3.0, 1.5)));
        for (int i = 0;i < 3 ;i++ ) {
            double y = 2.0*pow(-p/3.0, 0.5)*cos((phi + 2.0* M_PI * i)/3.0);
            double x = y - r/3.0;
            outputs.append(komplex(x));
        }
    }else if(D>0){
        double u = cbrt(-q/2.0 + pow(D, 0.5));
        double v = cbrt(-q/2.0 - pow(D, 0.5));
        double y1 = u+v;
        double x1 =  y1 - r/3.0;
        double realy = -0.5*(u+v);
        double realx = realy - r/3.0;
        double imag = 0.5 * pow(3.0, 0.5)*(u-v);
        outputs.append(komplex(x1));
        outputs.append(komplex(realx, imag));
        outputs.append(komplex(realx, -imag));
    }else{
        double y1 = 2*cbrt(-q/2.0);
        double y2 = -cbrt(-q/2.0);
        double x1 = y1 - r/3.0;
        double x2 = y2 - r/3.0;
        outputs.append(komplex(x1));
        outputs.append(komplex(x2));
        outputs.append(komplex(x2));
    }
    return outputs;
}
QVector<komplex> numerisch(QVector<double> input){
    //Durand-Kerner Algorithmus
    //https://youtu.be/5JcpOj2KtWc
    QVector<double> inputs;
    for(int i = input.count() - 1; i >= 0; i--){//sortiert die ganze Liste um
        inputs.append(input.at(i));//somit ist der Term mit dem niedrigsten Grad ganz vorne
    }
    //input ist normal sortiert (größte Potenz ist vorne) und inputs genau anders herum
    QVector<komplex> appvalues;//Approximation Values

    const double genauigkeit = pow(10, -9);//Grenze für die Änderung von einer Iteration zur nächsten
    //Wenn sich der Wert unterhalb der genauigkeit geändert  hat, dann gilt er als Nullstelle
    double aktuelle_genauigkeit = INFINITY;//wird auf unendlich initialisiert
    //Theoretisch müsste jede Zahl kleiner sein

    //Hier werden die Startwerte initialisiert
    //optimalerweise auf einem komplexen Kreis und alle Werte sollten gleichmäßig verteilt sein
    //Auch sollte die reelle Achse vermieden werden. genauso wie komplex konjugierte Paare

    double offset = M_PI/(2.0*inputs.count());//dieser vermeidet die reelle Achse und die Paare
    double winkel = (2*M_PI)/inputs.count();//dieser kümmert sich um die gleichmäßige Verteilung
    double radius = pow(abs(inputs.at(0)/inputs.back()), (1/inputs.count()));//Das ist der radius des Kreises
    for(int i = 0; i < inputs.count()-1; i++){//ein Polynom nten Grades hat n Lösungen und n+1 monome
        komplex x;
        x.set_real(radius);
        x.set_imag(offset + i * winkel);
        x.toKaart();
        appvalues.append(x);

    }//jetzt haben wir die Startwerte auf einem Kreis gleichmäßig verteilt und um einen winkeloffset verschoben

    QVector<bool> NullstelleGefunden;
    foreach(komplex x, appvalues){
        NullstelleGefunden.append(false);
    }

    QVector<komplex> aktuelle_appvalues = appvalues;
    while(aktuelle_genauigkeit > genauigkeit){//solange die Änderung nicht klein genug ist...
        double temp_genauigkeit = 0;
        for(int i = 0; i < appvalues.count(); i++){
            if(NullstelleGefunden.at(i) == false){
                komplex appValue = appAusrechnen(input, appvalues, i);//rechnet eine genauere Nullstelle aus
                if (((appValue-appvalues.at(i)).betrag())>temp_genauigkeit){//Wenn die Änderung größer war wie tempgenauigkeit...
                    temp_genauigkeit = (appValue-appvalues.at(i)).betrag();//dann wird diese Änderung zu tempgenauigkeit
                    if((appValue-appvalues.at(i)).betrag()<genauigkeit){
                        NullstelleGefunden[i] = true;
                    }
                }
                aktuelle_appvalues[i] = appValue;//die Nullstelle wird gespeichert
            }
        }
        //nachdem jede Nullstelle eine weitere Iteration durchgemacht hat...
        if(aktuelle_genauigkeit>temp_genauigkeit){//wird geschaut ob die größte Abweichung kleiner ist als die von den vorherigen Iterationen
            aktuelle_genauigkeit = temp_genauigkeit;//Wenn ja wird diese geupdated
        }
        appvalues = aktuelle_appvalues;//Die Liste aus der vorherigen Iteration wird die aktuelle Iteration
    }//Wenn dann jede Nullstelle die oben festgelegte Geanuigkeit erreicht hat, ist der Vorgang abgeschlossen

    return appvalues;//und die Werte werden zurückgegeben
}
komplex yWert(QVector<double> input, komplex x){
    //Rechnet bei einem gegebenen Polynom und einem gegebenen x den yWert an der Stelle x aus
    //input muss so sortiert sein, dass der höchste Grad an Index 0 ist
    QVector<double> inputs;
    for(int i = input.count() - 1; i >= 0; i--){//sortiert die ganze Liste um. somit ist der Term mit dem niedrigsten Grad ganz vorne
        inputs.append(input.at(i));
    }
    komplex y(0, 0);//neutrales Element bezüglich der Addition
    for(int i = 0; i < inputs.count(); i++){
        //da jetzt der Index mit der Potenz übereinstimmt, funktioniert folgendes:
        y = y + pow(x, i) * inputs.at(i);
    }
    if(y.get_real() != y.get_real()){
        debug("NAN 4");
    }
    return y;
}
komplex appAusrechnen(QVector<double> inputs, QVector<komplex> appValues, int i){
    //rechnet bei gegebenen Polynom, bei den gegebenen Nullstellen einer Iteration und dem index der nullstelle die berechnet werden soll
    //die Nullstelle des index für die nächste Generation aus
    komplex nenner(1,0);//neutrales Element bezüglich der Multiplikation
    komplex app;
    komplex x = appValues.at(i);
    for(int j = 0; j < appValues.count(); j++){
        if(j != i){//für den Nenner werden alle (x-Nullstelle) aufeinandermultipliziert, außer die Nullstelle für das das berechnet werden soll
            nenner = nenner * (x - appValues.at(j));
            if(nenner.get_real() != nenner.get_real()){
                debug("NAN 7");
            }
        }
    }
    komplex y = yWert(inputs, x);//rechnet den yWert der aktuellen Nullstelle aus
    app = x - (y / nenner);//hier wird die nächste Iteration dieser Nullstelle bestimmt
    if(app != app || app.get_imag()==INFINITY){
        debug("NAN 5");
    }
    return app;
}
QVector<komplex> PolynomHandler(QVector<double> inputs){
    int grad = inputs.count()-1;
    QVector<komplex> outputs;
    if(grad < 1){
        debug("Dieses Polynom ist nicht implementiert");
        return outputs;
    }else if(grad == 1){
        return linear(inputs);
    }else if(grad == 2){
        return pqFormel(inputs);
    }else if(grad == 3){
        return cardano(inputs);
    }else{
        return numerisch(inputs);
    }
}
void Nullstellenfinder::berechnen(){
    QString koeffizientenstring = ui->lineKoeffizienten->text();
    ui->textNullstellen->clear();
    QVector<double> inputs;
    auto liste = koeffizientenstring.split(';');
    foreach(QString zahl, liste){
        if (zahl == ""){
            inputs.append(0.0);
        }else{
            inputs.append(zahl.toDouble());
        }
    }
    QVector<komplex> outputs = PolynomHandler(inputs);
    foreach(komplex z, outputs){

        ui->textNullstellen->append(z.toQstring());
        ui->textNullstellen->append("\n");
        if(z.get_real() != z.get_real()){
            debug("NAN 6");
        }
    }
    QString equation;
    int j = inputs.count();
    for(int i = 0; i < j; i++){
        int grad = j-i-1;
        QString x;
        double y = inputs.at(i);
        if(y != 0.0){
            if(y > 0 && i !=0){
                x += "+";
            }
            if(y == -1){
                x += "-";
            }else if(y == 1){

            }else{
                x +=  QString::number(y);
            }
            if(grad == 0){
                if(y == 1 || y==-1){
                    x += "1";
                }


            }else if(grad == 1){
                x += "x";
            }else{
                x += "x^" + QString::number(grad);
            }
            x += " ";
        }
        equation.append(x);
    }
    equation.append(" = 0");
    ui->label_Equation->setText(equation);


}

