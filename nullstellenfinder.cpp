#include "nullstellenfinder.h"
#include "ui_nullstellenfinder.h"

Nullstellenfinder::Nullstellenfinder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Nullstellenfinder)
{
    ui->setupUi(this);

    ui->label_Equation->clear();
    connect(ui->ButtonBerechnen, SIGNAL(released()), this, SLOT(berechnen()));
    connect(ui->lineKoeffizienten, SIGNAL(textChanged(const QString&)), this, SLOT(berechnen()));
    connect(ui->ButtonMenu, SIGNAL(released()), this, SLOT(handler()));
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
QVector<komplex> linear(QVector<komplex> inputs){
    komplex erg = (inputs.at(1)/inputs.at(0)) * -1;
    QVector<komplex> outputs;
    outputs.append(komplex(erg));
    return outputs;
}

void Nullstellenfinder::handler(){//soll das Menu handlen
    auto y = new MainWindow();
    y->show();
    this->close();
}
void Nullstellenfinder::berechnen(){
    QString koeffizientenstring = ui->lineKoeffizienten->text();
    ui->textNullstellen->clear();
    QVector<double> inputs;
    auto liste = koeffizientenstring.split(',');
    foreach(QString zahl, liste){
        if (zahl == ""){
            inputs.append(0.0);
        }else{
            inputs.append(zahl.toDouble());
        }
    }
    QVector<komplex> outputs = PolynomHandler(inputs);
    foreach(komplex z, outputs){
        z.runden(6);
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
