#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


//#include "matrizen.h"
#include "basictaschenrechner.h"
#include "nullstellenfinder.h"
#include "matrix.h"
#include "random.h"
#include "regression.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void handler();

};

#endif // MAINWINDOW_H
