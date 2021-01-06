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
    void NumPressed();//reagiert sobald eine Zahl gedrückt wird
    void MathButtonpressed();//reagiert sobald eine Rechenoperation gedrückt wird
    void EqualsButton();//reagiert wenn der = gedrückt wird
    void ChangeNumberSign();//reagiert wenn der Vorzeichenwechsel gedrückt wurde
    void clear();//reagiert wenn AC gedrückt wird
    void KommaButtonpressed();//reagiert wenn das Komma gedrückt wird
    void handler();//kümmert sich um das Öffnen anderer Fenster
    void Fakultaet();//berechnet die fakultät
    void oneClick();//kümmert sich um alle Berechnungen, die nur einen Input benötigen (zb. Fakultät, sqrt...
    void labelClear();//löscht die Fehlermeldung
};

#endif // BASICTASCHENRECHNER_H
