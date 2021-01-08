#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "basictaschenrechner.h"
#include "allgemein.h"
#include "nullstellenfinder.h"
#include "komplex.h"
#include "nullstellenfinder.h"
#include "matrix.h"
#include "matrizen.h"
#include "random.h"

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
