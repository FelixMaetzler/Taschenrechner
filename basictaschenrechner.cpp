#include "basictaschenrechner.h"
#include "ui_basictaschenrechner.h"


double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


basicTaschenrechner::basicTaschenrechner(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::basicTaschenrechner)
{
    ui->setupUi(this);


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

    connect(ui->ButtonEquals, SIGNAL(released()), this, SLOT(EqualsButton()));
    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clear()));

    connect(ui->actionMenu, SIGNAL(triggered()),this , SLOT(handler()));
}

basicTaschenrechner::~basicTaschenrechner()
{
    delete ui;
}

void basicTaschenrechner::NumPressed(){
    QPushButton* Button = (QPushButton*) sender();
    QString butVal = Button->text();
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){
        ui->Display->setText(butVal);
    }else{
        QString newVal = displayVal + butVal;
        double dblBNewval = newVal.toDouble();
        ui->Display->setText(QString::number(dblBNewval, 'g', 16));//macht das nach 16 Stellen die Exponentendarstellung benutzt wird
    }
 }
    void basicTaschenrechner::MathButtonpressed(){
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
       } else{
           subTrigger = true;
       }
    ui->Display->setText("");
    }

   void basicTaschenrechner::EqualsButton(){
        double solution = 0.0;
        QString displaVal = ui->Display->text();
        double dblDisplayVal = displaVal.toDouble();
        if(addTrigger || subTrigger || multTrigger || divTrigger){
            if(addTrigger){
                solution = calcVal + dblDisplayVal;
            }else if(subTrigger){
                solution = calcVal - dblDisplayVal;
            }else if(divTrigger){
                solution = calcVal / dblDisplayVal;
            }else{
                solution = calcVal * dblDisplayVal;
            }

            ui->Display->setText(QString::number(solution));
        }

   }

   void basicTaschenrechner::ChangeNumberSign(){
       QString displayVal = ui->Display->text();
       QRegExp reg("[-]?[0-9.]*");
       if(reg.exactMatch(displayVal)){
           double dblDisplayVal = displayVal.toDouble();
           double dblDisplayvalSign = dblDisplayVal * -1;
           ui->Display->setText(QString::number(dblDisplayvalSign));
       }
   }

   void basicTaschenrechner::clear(){
       ui->Display->setText(QString::number(0));
   }

   void basicTaschenrechner::handler(){
       QAction* x = (QAction*) sender();
       auto Buttonname = x->text();

      qDebug() << QString(Buttonname);
      if(Buttonname == "Menu"){

          auto y = new MainWindow();
          y->show();
          this->close();
      }
   }
