#include "mainwindow.h"
#include "ui_mainwindow.h"



double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->Display->setText(QString::number(calcVal));//zeigt auf dem Display den aktuellen Wert an. dafür muss er aber noch in QString konvertiert werden
    auto numButtons = new QVector<QPushButton*>();
    for (int i = 0; i < 10; ++i) {
        QString ButName = "Button" + QString::number(i);
        numButtons->append(MainWindow::findChild<QPushButton*>(ButName));//sucht nach Elementen die ButName heißen und fügt sie der Liste hinzu
        connect(numButtons->at(i), SIGNAL(released()), this, SLOT(NumPressed()));//wenn ein Button losgelassen wird, dann wird die Funktion NumPressed uffgerufe
    }

    connect(ui->ButtonAdd, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonSub, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonDiv, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ButtonMult, SIGNAL(released()), this, SLOT(MathButtonpressed()));

    connect(ui->ButtonEquals, SIGNAL(released()), this, SLOT(EqualsButton()));
    connect(ui->ButtonChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->ButtonClear, SIGNAL(released()), this, SLOT(clear()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
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
    void MainWindow::MathButtonpressed(){
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

   void MainWindow::EqualsButton(){
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

   void MainWindow::ChangeNumberSign(){
       QString displayVal = ui->Display->text();
       QRegExp reg("[-]?[0-9.]*");
       if(reg.exactMatch(displayVal)){
           double dblDisplayVal = displayVal.toDouble();
           double dblDisplayvalSign = dblDisplayVal * -1;
           ui->Display->setText(QString::number(dblDisplayvalSign));
       }
   }

   void MainWindow::clear(){
       ui->Display->setText(QString::number(0));
   }
