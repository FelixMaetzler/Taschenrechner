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
qDebug()<<action->text();
    ui->menubar->addMenu(menu);

connect(MainWindow::findChild<QAction*>("BasicTaschenrechner"), SIGNAL(triggered()),this , SLOT(handler()));

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
}
