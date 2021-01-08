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

    action = new QAction("Random");
    action->setObjectName("Random");
    action->setParent(menu);
    menu->addAction(action);
    ui->menubar->addMenu(menu);

    connect(MainWindow::findChild<QAction*>("BasicTaschenrechner"), SIGNAL(triggered()),this , SLOT(handler()));
    connect(MainWindow::findChild<QAction*>("Nullstellenfinder"), SIGNAL(triggered()),this , SLOT(handler()));
    connect(MainWindow::findChild<QAction*>("Matrixrechner"), SIGNAL(triggered()),this , SLOT(handler()));
    connect(MainWindow::findChild<QAction*>("Random"), SIGNAL(triggered()),this , SLOT(handler()));

    matrizen matrix(4,4);
    matrix.set_wert(5, 0,0);
    matrix.set_wert(2, 1,0);
    matrix.set_wert(4, 2,0);
    matrix.set_wert(5, 3,0);

    matrix.set_wert(5, 0,1);
    matrix.set_wert(1, 1,1);
    matrix.set_wert(2, 2,1);
    matrix.set_wert(-8, 3,1);

    matrix.set_wert(-3, 0,2);
    matrix.set_wert(9, 1,2);
    matrix.set_wert(-6, 2,2);
    matrix.set_wert(-9, 3,2);

    matrix.set_wert(-7, 0,3);
    matrix.set_wert(6, 1,3);
    matrix.set_wert(-5, 2,3);
    matrix.set_wert(2, 3,3);
    matrix.charakteristischesPolynom();

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
    if(Buttonname == "Random"){

        auto y = new random();
        y->show();
        this->close();
    }
}
