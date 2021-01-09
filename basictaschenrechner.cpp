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
    auto enter_num = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    auto enter = new QShortcut(QKeySequence(Qt::Key_Return), this);
    connect(enter, SIGNAL(activated()), this, SLOT(EqualsButton()));
    connect(enter_num, SIGNAL(activated()), this, SLOT(EqualsButton()));

    auto add = new QShortcut(QKeySequence(Qt::Key_Plus), this);
    add->setObjectName("Add");
    auto sub = new QShortcut(QKeySequence(Qt::Key_Minus), this);
    sub->setObjectName("Sub");
    auto mult = new QShortcut(QKeySequence("*"), this);
    mult->setObjectName("Mult");
    auto div = new QShortcut(QKeySequence(Qt::Key_Slash), this);
    div->setObjectName("Div");
    connect(add, SIGNAL(activated()), this, SLOT(MathButtonpressed()));
    connect(sub, SIGNAL(activated()), this, SLOT(MathButtonpressed()));
    connect(mult, SIGNAL(activated()), this, SLOT(MathButtonpressed()));
    connect(div, SIGNAL(activated()), this, SLOT(MathButtonpressed()));

    auto komma = new QShortcut(QKeySequence(","), this);
    connect(komma, SIGNAL(activated()), this, SLOT(KommaButtonpressed()));
    auto AC = new QShortcut(QKeySequence(Qt::Key_Backspace), this);
    connect(AC, SIGNAL(activated()), this, SLOT(clear()));

    auto num_1 = new QShortcut(QKeySequence("1"), this);
    num_1->setObjectName("Button_1");
    auto num_2 = new QShortcut(QKeySequence("2"), this);
    num_2->setObjectName("Button_2");
    auto num_3 = new QShortcut(QKeySequence("3"), this);
    num_3->setObjectName("Button_3");
    auto num_4 = new QShortcut(QKeySequence("4"), this);
    num_4->setObjectName("Button_4");
    auto num_5 = new QShortcut(QKeySequence("5"), this);
    num_5->setObjectName("Button_5");
    auto num_6 = new QShortcut(QKeySequence("6"), this);
    num_6->setObjectName("Button_6");
    auto num_7 = new QShortcut(QKeySequence("7"), this);
    num_7->setObjectName("Button_7");
    auto num_8 = new QShortcut(QKeySequence("8"), this);
    num_8->setObjectName("Button_8");
    auto num_9 = new QShortcut(QKeySequence("9"), this);
    num_9->setObjectName("Button_9");
    auto num_0 = new QShortcut(QKeySequence("0"), this);
    num_0->setObjectName("Button_0");
    connect(num_1, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_2, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_3, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_4, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_5, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_6, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_7, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_8, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_9, SIGNAL(activated()), this, SLOT(NumPressed()));
    connect(num_0, SIGNAL(activated()), this, SLOT(NumPressed()));

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

    connect(ui->ButtoMenu, SIGNAL(released()), this, SLOT(handler()));

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
    QPushButton* Button = (QPushButton*) sender();//ist ein pointer auf das Objekt, das diese Funktion uffruft
    //QString butVal = Button->text();//ruft den Text des Senders ab. das ist geanu die Zahl
    QString butVal = Button->objectName().at(Button->objectName().count()-1);
    QString displayVal = ui->Display->text();
    if(displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0){//wenn aufm TR eine Null steht
        if(komma){//und das komma zuvor gedrückt wurde
            butVal = "." + butVal;//ist der neue Wert
            komma = false;//und das Komma wird wieder auf false gesetzt
        }
        ui->Display->setText(butVal);//der neue Wert wird angezeigt
    }else{//falls keine Null da stand
        QString newVal;
        if(komma){//wenn das komma gedrückt worden ist
            newVal = displayVal +"." + butVal;
            komma = false;
        }else{//wennd as komma nicht gedrückt worden ist
            newVal = displayVal + butVal;//Hier werden Strings aneinander gehangen
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
    QString displayVal = ui->Display->text();//ruft die zahl aufm TR als String ab
    calcVal = displayVal.toDouble();//konvertiert diesen String zu nem double
    QPushButton* button = (QPushButton*) sender();//pointer zu Senderobjekt
    QString ButVal = button->objectName();//ruft den Text des senders ab
    //je nachdem welcher Button das war, wird der Trigger gesetzt
    if(ButVal.contains("Div")){
        divTrigger = true;
    }else if(ButVal.contains("Mult")){
        multTrigger = true;
    }else if(ButVal.contains("Add")){
        addTrigger = true;
    } else if(ButVal.contains("Sub")){
        subTrigger = true;
    }else{
        potTrigger = true;
    }
    ui->Display->setText("");//Text auf dem TR wird "gelöscht"
}

void basicTaschenrechner::EqualsButton(){
    labelClear();
    double solution = 0.0;
    QString displaVal = ui->Display->text();//ruft den auf dem TR angezeigten Wert ab
    double dblDisplayVal = displaVal.toDouble();//konvertiert ihn zu nem double
    if(addTrigger || subTrigger || multTrigger || divTrigger || potTrigger){//prüft ob eine Rechenoperation vorliegt
        //wenn ja, wird diese aufgeführt
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
    QRegExp reg("[-]?[0-9.]*");//erstellt ein bestimmtes Muster
    if(reg.exactMatch(displayVal)){//wenn die angezeigte Zahl genau diesem Muster entspricht
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayvalSign = dblDisplayVal * -1;//wird das vorzeichen umgedreht
        ui->Display->setText(QString::number(dblDisplayvalSign));//und angezeigt
    }
}

void basicTaschenrechner::clear(){
    labelClear();
    ui->Display->setText(QString::number(0));
}

void basicTaschenrechner::handler(){//soll das Menu handlen
    labelClear();
    auto y = new MainWindow();
    y->show();
    this->close();
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
        ui->Display->setText(QString::number(tgamma(val + 1)));//benutzt die Gamma Funktion. dadurch auch Fakultät von reellen Zahlen möglich
    }
}
void basicTaschenrechner::oneClick(){//kümmert sich um Funktionen die nur einen inputwert brauchen
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
