#include "random.h"
#include "ui_random.h"

random::random(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::random)
{
    ui->setupUi(this);

    connect(ui->lineEingabePrim, SIGNAL(textChanged(const QString&)), this, SLOT(erneuern()));
    connect(ui->lineEingabeAnderes, SIGNAL(textChanged(const QString&)), this, SLOT(erneuern()));
}

random::~random()
{
    delete ui;

}
QVector<long long> primFaktorZerlegung(long long n){
    QVector<long long> primfaktoren;
    if(n < 2){
        debug("keine PFZ möglich");
        return primfaktoren;
    }
    const long long anfangszahl = n;
    long long zaehler = 2;
    while (n != 1 && zaehler <= anfangszahl) {
        if(n % zaehler == 0){
            primfaktoren.append(zaehler);
            n = n / zaehler;
        }else{
            zaehler++;
        }
    }

    return primfaktoren;
}
void random::erneuern(){
    if(sender()->objectName().contains("Prim")){
        long long zahl = ui->lineEingabePrim->text().toLongLong();
        if(zahl > 1){
            auto faktoren = primFaktorZerlegung(zahl);
            QString text = "";
            foreach(int x, faktoren){
                text += QString::number(x) + ", ";
            }
            ui->linePrimfaktorzerlegung->setText(text);
        }
    }
    if(sender()->objectName().contains("Anderes")){
        QString eingelesen = ui->lineEingabeAnderes->text();
        auto zahlenString = eingelesen.split(",");
        QVector<long long> zahlen;
        foreach(auto x, zahlenString){
            zahlen.append(x.toULongLong());
        }
        auto GGT = ggT(zahlen);
        auto KGV = kgV(zahlen);
        ui->lineggT->setText(QString::number(GGT));
        ui->linekgV->setText(QString::number(KGV));
    }
}
long long kgV(QVector<long long> liste){
    QVector<QVector<long long>> sammlung;
    foreach(auto x, liste){
        sammlung.append(primFaktorZerlegung(x));
    }
    QVector<long long> allePrimfaktoren;
    foreach(auto x, sammlung){
        allePrimfaktoren.append(x);
    }
    std::sort(allePrimfaktoren.begin(), allePrimfaktoren.end());
    allePrimfaktoren.erase(std::unique(allePrimfaktoren.begin(), allePrimfaktoren.end()), allePrimfaktoren.end());
    long long wert = 1;
    foreach(auto x, allePrimfaktoren){
        int maxAnzahl = -INFINITY;
        for(int i = 0; i < sammlung.count(); i++){
            int aktuelleAnzahl = anzahlEnthalten(sammlung.at(i), x);
            if(aktuelleAnzahl > maxAnzahl){
                maxAnzahl = aktuelleAnzahl;
            }
        }
        for(int i = 0; i < maxAnzahl; i++){
            wert *= x;
        }
    }

    return wert;
}
long long ggT(QVector<long long> liste){
    if(liste.count() == 1){
        if(liste.at(0) > 1){
            return liste.at(0);
        }else{
            return 1;
        }
    }
    QVector<QVector<long long>> sammlung;
    foreach(auto x, liste){
        sammlung.append(primFaktorZerlegung(x));
    }
    sammlung = sortieren(sammlung);
    foreach(auto x, sammlung.at(0)){
        for(int i = sammlung.count() - 1; i > 0; i--){
            bool enthalten = istEnthalten(sammlung.at(i), x);
            if(!enthalten){
                break;
            }else if(i == 1){
                return x;
            }
        }
    }
    return 1;
}
bool istEnthalten(QVector<long long> liste, long long n){
    foreach(auto x, liste){
        if(n == x){
            return true;
        }
    }
    return false;
}
QVector<QVector<long long>> sortieren(QVector<QVector<long long>> liste){
    QVector<QVector<long long>> erg;
    while(liste.count() != 0){
        int anzahl = INFINITY;
        int index = INFINITY;
        for(int i = 0; i < liste.count(); i++){
            if(liste.at(i).count() < anzahl){
                anzahl = liste.at(i).count();
                index = i;
            }
        }
        erg.append(liste.at(index));
        liste.remove(index);
    }
    return erg;
}
int anzahlEnthalten(QVector<long long> liste, long long n){
    int counter = 0;
    foreach(auto x, liste){
        if(x == n){
            counter++;
        }else if(x > n){
            break;
        }
    }
    return counter;
}
