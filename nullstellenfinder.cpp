#include "nullstellenfinder.h"
#include "ui_nullstellenfinder.h"

Nullstellenfinder::Nullstellenfinder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nullstellenfinder)
{
    ui->setupUi(this);


}

Nullstellenfinder::~Nullstellenfinder()
{
    delete ui;
}

QVector<komplex> abcFormel(QVector<double> inputs){
    QVector<komplex> outputs;
    komplex a(inputs.at(0));
    komplex b(inputs.at(1));
    komplex c(inputs.at(2));
    outputs.append((b*-1+pow(b*b-a*c*4,0.5))/(a*-2));
    outputs.append((b*-1-pow(b*b-a*c*4,0.5))/(a*-2));
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
    //https://youtu.be/5JcpOj2KtWc
    QVector<double> inputs;
    for(int i = input.count() - 1; i >= 0; i--){//sortiert die ganze Liste um. somit ist der Term mit dem niedrigsten Grad ganz vorne
        inputs.append(input.at(i));
    }
    QVector<komplex> appvalues;//Approximation Values

    const double genauigkeit = pow(10, -9);
    double aktuelle_genauigkeit = INFINITY;
    double offset = M_PI/(2.0*inputs.count());
    double winkel = (2*M_PI)/inputs.count();
    double radius = pow(abs(inputs.at(0)/inputs.back()), (1/inputs.count()));
    for(int i = 0; i < inputs.count()-1; i++){
        komplex x;
        x.set_real(radius);
        x.set_imag(offset + i * winkel);
        x.toKaart();
        appvalues.append(x);

    }//startingValues ferig



    QVector<komplex> aktuelle_appvalues = appvalues;
    while(aktuelle_genauigkeit > genauigkeit){
        double temp_genauigkeit = 0;
        for(int i = 0; i < appvalues.count(); i++){

            komplex appValue = appAusrechnen(input, appvalues, i);
            if (((appValue-appvalues.at(i)).betrag())>temp_genauigkeit){
                temp_genauigkeit = (appValue-appvalues.at(i)).betrag();
            }
            aktuelle_appvalues[i] = appValue;
        }
        if(aktuelle_genauigkeit>temp_genauigkeit){
            aktuelle_genauigkeit = temp_genauigkeit;
        }
        appvalues = aktuelle_appvalues;
    }
return appvalues;
}
komplex yWert(QVector<double> input, komplex x){
    //input müssen so sortiert sein, dass der höchste Grad an Index 0 ist
    QVector<double> inputs;
    for(int i = input.count() - 1; i >= 0; i--){//sortiert die ganze Liste um. somit ist der Term mit dem niedrigsten Grad ganz vorne
        inputs.append(input.at(i));
    }
    komplex y(0, 0);
    for(int i = 0; i < inputs.count(); i++){
        y = y + pow(x, i) * inputs.at(i);
    }
    return y;
}
komplex appAusrechnen(QVector<double> inputs, QVector<komplex> appValues, int i){
    komplex nenner(1,0);
    komplex app;
    komplex x = appValues.at(i);
    for(int j = 0; j < appValues.count(); j++){
        if(j != i){
            nenner = nenner * (x - appValues.at(j));
        }
    }
komplex y = yWert(inputs, x);
app = x - (y / nenner);
return app;
}

