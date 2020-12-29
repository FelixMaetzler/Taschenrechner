#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setMenuBar(addmenu(ui->menubar));
    QMenu* menu = new QMenu("TR");
    menu->setObjectName("TR");
    menu->setParent(this);
    QAction* action = new QAction("Menu");
    action->setObjectName("Menu");
    action->setParent(menu);
    menu->addAction(action);

action = new QAction("BasicTaschenrechner");
action->setObjectName("BasicTaschenrechner");
action->setParent(menu);
    menu->addAction(action);

    action = new QAction("Nullstellenfinder");
    action->setObjectName("Nullstellenfinder");
    action->setParent(menu);
        menu->addAction(action);
    ui->menubar->addMenu(menu);

connect(MainWindow::findChild<QAction*>("BasicTaschenrechner"), SIGNAL(triggered()),this , SLOT(handler()));
connect(MainWindow::findChild<QAction*>("Nullstellenfinder"), SIGNAL(triggered()),this , SLOT(handler()));

QVector<double> inputs;
inputs.append(1);
inputs.append(2);
inputs.append(3);
inputs.append(4);
inputs.append(5);
inputs.append(6);
inputs.append(7);

auto outputs = numerisch(inputs);
foreach(komplex elem, outputs){
    debug(elem);
}
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handler(){
    QAction* x = (QAction*) sender();
    auto Buttonname = x->text();

   qDebug() << QString(Buttonname);
   if(Buttonname == "BasicTaschenrechner"){

       auto y = new basicTaschenrechner();
       y->show();
       this->close();
   }
   if(Buttonname == "Nullstellenfinder"){

       auto y = new Nullstellenfinder();
       y->show();
       this->close();
   }
}
