#ifndef BASICTASCHENRECHNER_H
#define BASICTASCHENRECHNER_H

#include <QMainWindow>
#include <mainwindow.h>

#include <allgemein.h>

namespace Ui {
class basicTaschenrechner;
}

class basicTaschenrechner : public QMainWindow
{
    Q_OBJECT

public:
    explicit basicTaschenrechner(QWidget *parent = nullptr);
    ~basicTaschenrechner();

private:
    Ui::basicTaschenrechner *ui;

private slots:
    void NumPressed();
    void MathButtonpressed();
    void EqualsButton();
    void ChangeNumberSign();
    void clear();
    void handler();
};

#endif // BASICTASCHENRECHNER_H
