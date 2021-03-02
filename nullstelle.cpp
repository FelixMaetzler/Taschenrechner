#include "nullstelle.h"

nullstelle::nullstelle()
{

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
double yWert(QVector<double> input, double x){
    //Rechnet bei einem gegebenen Polynom und einem gegebenen x den yWert an der Stelle x aus
    //input muss so sortiert sein, dass der höchste Grad an Index 0 ist
    QVector<double> inputs;
    for(int i = input.count() - 1; i >= 0; i--){//sortiert die ganze Liste um. somit ist der Term mit dem niedrigsten Grad ganz vorne
        inputs.append(input.at(i));
    }
    double y = 0;//neutrales Element bezüglich der Addition
    for(int i = 0; i < inputs.count(); i++){
        //da jetzt der Index mit der Potenz übereinstimmt, funktioniert folgendes:
        y = y + pow(x, i) * inputs.at(i);
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
    if(grad < 1){
        debug("Dieses Polynom ist nicht implementiert");
        return QVector<komplex>();
    }else if(grad == 1){
        return linear(inputs);
    }else if(grad == 2){
        return pqFormel(inputs);
    }else if(grad == 3){
        return cardano(inputs);
    }else{
        //return numerisch(inputs);
        auto hajonet = toKomplex(inputs);
        auto outputs_ptr = new QVector<komplex>();
        newtonNullstellen(hajonet, outputs_ptr);
        QVector<komplex> outputs = *outputs_ptr;
        delete outputs_ptr;
        return outputs;
    }
}

QVector<double> toReal(QVector<komplex> liste){
    QVector<double> erg;
    foreach(auto x, liste){
        if(!istUngefaerGleich(x.get_imag(),0)){
            debug("Umwandlung zu real geht nicht. Der imaginäre Anteil ist != 0");
            return erg;
        }
    }
    foreach(auto x, liste){
        erg.append(x.get_real());
    }
    return erg;
}
QVector<komplex> toKomplex(QVector<double> liste){
    QVector<komplex> erg;
    foreach(auto x, liste){
        erg.append(komplex(x,0));
    }
    return erg;
}
bool istUngefaerGleich(double x, double y, double genauigkeit){
    double differenz = abs(x-y);
    if(differenz < genauigkeit){
        return true;
    }else{
        return false;
    }
}
bool istUngefaerGleich(komplex x, komplex y , double genauigkeit){
    if(istUngefaerGleich(x.get_real(), y.get_real(), genauigkeit)){
        if(x.get_imag(), y.get_imag(), genauigkeit){
            return true;
        }
    }
    return false;
}
QVector<komplex> ableiten(QVector<komplex> funktion){
    QVector<komplex> erg;
    if(funktion.empty()){
        return erg;
    }
    int maxPotenz = funktion.count() - 1;
    for(int i = 0; i < funktion.count(); i++){
        komplex koeffizient = funktion.at(i);
        double multiplikator = maxPotenz - i;
        erg.append(koeffizient * multiplikator);
    }

    erg.remove(maxPotenz);
    return erg;
}
QVector<komplex> listeReversen(QVector<komplex> liste){
    QVector<komplex> reversed;
    for(int i = liste.count() - 1; i >= 0; i--){
        reversed.append(liste.at(i));
    }
    return reversed;
}
QVector<double> listeReversen(QVector<double> liste){
    return toReal(listeReversen(toKomplex(liste)));
}
QVector<komplex> hornerschema(QVector<komplex> funktion, komplex nullstelle){
    QVector<komplex> erg;
    QVector<komplex> zwischenerg;
    /*
    if(!istUngefaerGleich(yWert(funktion, nullstelle), komplex(0,0), pow(10, -1))){
        debug("hornerschema kann nicht angewandt werden. ist keine Nullstelle!");
        return erg;
    }
    */
    //Hornerschema
    zwischenerg.append(0);
    for(int i = 0; i < funktion.count(); i++){
        komplex wert = (funktion.at(i) + zwischenerg.at(i));
        erg.append(wert);
        zwischenerg.append(wert * nullstelle);
    }
    if(erg.empty()){
        return erg;
    }
    if(!istUngefaerGleich(erg.last(), komplex(0,0), pow(10,-3))){
        debug("hornerschema kann nicht angewandt werden. ist keine Nullstelle!");
        erg.clear();
        return erg;
    }else{
        erg.remove(erg.count()-1);
        return erg;
    }
}
komplex yWert(QVector<komplex> funktion, komplex x){
    komplex y(0,0);
    funktion = listeReversen(funktion);
    for(int i = 0; i < funktion.count(); i++){
        komplex koeffizient = funktion.at(i);
        y = y + (koeffizient * pow(x, i));
    }
    return y;
}
komplex newton(QVector<komplex> funktion, komplex startwert){
    QVector<komplex> ableitung = ableiten(funktion);
    komplex nullstelle = startwert;
    komplex neueNullstelle;
    komplex neuerWert;

    bool NullstelleGefunden = false;
    int counter1 = 0;
    int maxCounter1 = 1000;
    int counter2 = 1;
    int maxCounter2 = 100;
    while(counter2 < maxCounter2){
        while(counter1 < maxCounter1){
            komplex wert = yWert(funktion, nullstelle);
            komplex wertAbleitung = yWert(ableitung, nullstelle);
            if(istUngefaerGleich(wertAbleitung, komplex(0,0))){
                break;
            }
            neueNullstelle = nullstelle - (wert/wertAbleitung);
            neuerWert = yWert(funktion, neueNullstelle);
            if(istUngefaerGleich(wert, neuerWert)){
                NullstelleGefunden = true;
                break;
            }
            nullstelle = neueNullstelle;
            counter1++;
        }
        if(NullstelleGefunden){
            break;
        }

        nullstelle = startwert * pow(-1, counter2) * counter2;
        counter2++;
    }
    if(NullstelleGefunden){
        return nullstelle;
    }else{
        debug("Nullstelle konnte nicht gefunden werden");
        return komplex(0,0);
    }
}
void newtonNullstellen(QVector<komplex> funktion, QVector<komplex>* ergebnisse){
    QVector<komplex> erg;
    foreach(auto x, funktion){
        if(x.betrag() > pow(10, 9)){
            debug("Polynom ist zu groß um die Newtonnullstellen zu berechen");
            return;
        }
    }
    int grad = funktion.count() - 1;
    if(grad == 2){
        erg.append(pqFormel(funktion));

    }else{
        komplex nullstelle = newton(funktion);
        nullstelle.runden();
        erg.append(nullstelle);
        auto neueFunktion = hornerschema(funktion, nullstelle);
        newtonNullstellen(neueFunktion, ergebnisse);
    }
    ergebnisse->append(erg);
}
QVector<komplex> pqFormel(QVector<komplex> inputs){
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
