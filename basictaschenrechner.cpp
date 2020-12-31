#include "basictaschenrechner.h"
#include "ui_basictaschenrechner.h"


double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool potTrigger = false;

bool komma = false;


basicTaschenrechner::basicTaschenrechner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::basicTaschenrechner)
{
    ui->setupUi(this);
    labelClear();

    ui->Display->setText(QString::number(calcVal));//zeigt auf dem Display den aktuellen Wert an. dafür muss er aber noch in QString konvertiert werden
    auto numButtons = new QVector<QPushButton*>();
    for (int i = 0; i < 10; ++i) {
        QString ButName = "Button" + QString::number(i);
        numButtons->append(basicTaschenrechner::findChild<QPushButton*>(ButName));//sucht nach Elementen die ButName heißen und fügt sie der Liste hinzu
        connect(numButtons->at(i), SIGNAL(released()), this, SLOT(NumPressed()));//wenn ein Button losgelassen wird, dann wird die Funktion NumPressed uffgerufe
    }

    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonSub, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonDiv, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonMult, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonPotenz, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonKomma, SIGNAL(released()), this, SLOT(KommaButtonpressed()));


    connect(ui->ButtonEquals, SIGNAL(released()), this, SLOT(EqualsButton()));
    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clear()));
    connect(ui->ButtonFakulaet, SIGNAL(released()), this, SLOT(Fakultaet()));
    connect(ui->ButtonKubikwurzel, SIGNAL(released()), this, SLOT(oneClick()));
    connect(ui->ButtonQuadrat, SIGNAL(released()), this, SLOT(oneClick()));
    connect(ui->ButtonQuadratwurzel, SIGNAL(released()), this, SLOT(oneClick()));
    connect(ui->ButtonProzent, SIGNAL(released()), this, SLOT(oneClick()));



    connect(ui->actionMenu, SIGNAL(triggered()),this , SLOT(handler()));
}

basicTaschenrechner::~basicTaschenrechner()
{
    delete ui;
}
void basicTaschenrechner::KommaButtonpressed(){
    labelClear();
    komma = true;
}
void basicTaschenrechner::NumPressed(){
    labelClear();
    QPushButton* Button = (QPushButton*) sender();
    QString butVal = Button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
        if(komma){
            butVal = "." + butVal;
            komma = false;
        }
        ui->Display->setText(butVal);
    }else{
        QString newVal;
        if(komma){
            newVal = displayVal +"." + butVal;
            komma = false;
        }else{
            newVal = displayVal + butVal;
        }

        double dblBNewval = newVal.toDouble();
        ui->Display->setText(QString::number(dblBNewval, 'g', 16));//macht das nach 16 Stellen die Exponentendarstellung benutzt wird
    }
}
void basicTaschenrechner::MathButtonpressed(){
    labelClear();
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton* button = (QPushButton*) sender();
    QString ButVal = button->text();
    if(QString::compare(ButVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }else if(QString::compare(ButVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }else if(QString::compare(ButVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else if(QString::compare(ButVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    }else{
        potTrigger = true;
    }
    ui->Display->setText("");
}

void basicTaschenrechner::EqualsButton(){
    labelClear();
    double solution = 0.0;
    QString displaVal = ui->Display->text();
    double dblDisplayVal = displaVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger || potTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }else if(divTrigger){
            solution = calcVal / dblDisplayVal;
        }else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        }else{
            solution = pow(calcVal, dblDisplayVal);
        }

        ui->Display->setText(QString::number(solution));
    }

}

void basicTaschenrechner::ChangeNumberSign(){
    labelClear();
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayvalSign = dblDisplayVal * -1;
        ui->Display->setText(QString::number(dblDisplayvalSign));
    }
}

void basicTaschenrechner::clear(){
    labelClear();
    ui->Display->setText(QString::number(0));
}

void basicTaschenrechner::handler(){
    labelClear();
    QAction* x = (QAction*) sender();
    auto Buttonname = x->text();

    qDebug() << QString(Buttonname);
    if(Buttonname == "Menu"){

        auto y = new MainWindow();
        y->show();
        this->close();
    }
}
void basicTaschenrechner::Fakultaet(){
    labelClear();

    QString displayVal = ui->Display->text();
    double val = displayVal.toDouble();
    /*
    int x = val;//castet den double in ein int. nachkommastellen werden abgesdchnitten
    if(x == val){//wenns keine Nachkommastellen gab...
        if(x == 0){
            ui->Display->setText(QString::number(1));
            return;
        }
        if(x > 25){
            //fehler! Zahl zu groß
            ui->labelFehlermeldung->setText("Zahl zu groß");
            return;
        }
        long long int erg = 1;
        for (int i = 1;i <= x;i++ ) {
            erg *= i;
        }
        ui->Display->setText(QString::number(erg));
    }else{
        //Fehler! keine Ganzzahl
        ui->labelFehlermeldung->setText("keine Ganzzahl");
    }
    */
    if(val > 170){
        ui->labelFehlermeldung->setText("Zahl zu groß");
    }else if(val == -1){
        ui->labelFehlermeldung->setText("-1! ist nicht definiert!");
    }else{
        ui->Display->setText(QString::number(tgamma(val + 1)));
    }
}
void basicTaschenrechner::oneClick(){
    labelClear();
    QString displayVal = ui->Display->text();
    double v = displayVal.toDouble();
    QPushButton* button = (QPushButton*) sender();
    if(button->text()=="^2"){
        ui->Display->setText(QString::number(pow(v, 2)));
    }
    if(button->text()=="sqrt"){
        if(v < 0){
            ui->labelFehlermeldung->setText("keine Quadratwurzel von negativen Zahlen");
        }else{
            ui->Display->setText(QString::number(sqrt(v)));
        }

    }
    if(button->text()=="cbrt"){
        ui->Display->setText(QString::number(cbrt(v)));
    }
    if(button->text()=="%"){
        ui->Display->setText(QString::number(v/100));
    }

}

void basicTaschenrechner::labelClear(){
    ui->labelFehlermeldung->clear();
}
