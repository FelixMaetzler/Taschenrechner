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

    action = new QAction("Matrixrechner");
    action->setObjectName("Matrixrechner");
    action->setParent(menu);
    menu->addAction(action);
    ui->menubar->addMenu(menu);

    connect(MainWindow::findChild<QAction*>("BasicTaschenrechner"), SIGNAL(triggered()),this , SLOT(handler()));
    connect(MainWindow::findChild<QAction*>("Nullstellenfinder"), SIGNAL(triggered()),this , SLOT(handler()));
    connect(MainWindow::findChild<QAction*>("Matrixrechner"), SIGNAL(triggered()),this , SLOT(handler()));
    ///*
    matrizen matrix(4, 3);
    for(int zeilenzahl = 0; zeilenzahl < matrix.zeilenzahl(); zeilenzahl++){
        for(int spaltenzahl = 0; spaltenzahl < matrix.spaltenzahl(); spaltenzahl++){

            matrix.set_wert(spaltenzahl + zeilenzahl * matrix.zeilenzahl(), zeilenzahl, spaltenzahl);
        }
    }

    matrix.print();
    debug("");
    matrix.resize(5,5);
    matrix.print();
    //*/
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
    if(Buttonname == "Matrixrechner"){

        auto y = new Matrix();
        y->show();
        this->close();
    }
}
