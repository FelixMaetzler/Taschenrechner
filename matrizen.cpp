#include "matrizen.h"



matrizen::matrizen()
{

}
matrizen::matrizen(int zeilenzahl, int spaltenzahl){
    QVector<double> spalte;
    for(int i = 0; i < spaltenzahl; i++){
        spalte.append(0);
    }
    for(int i = 0; i < zeilenzahl; i++){
        this->matrix.append(spalte);
    }
}
double matrizen::get_wert(int zeilenzahl, int spaltenzahl) const {
    return this->matrix.at(zeilenzahl).at(spaltenzahl);
}
void matrizen::set_wert(double wert, int zeilenzahl, int spaltenzahl){
    this->matrix[zeilenzahl][spaltenzahl] = wert;
}
int matrizen::zeilenzahl() const {
    return this->matrix.count();
}
int matrizen::spaltenzahl() const {
    return this->matrix.at(0).count();
}
QVector<double> matrizen::get_spalte(int spaltenindex) const {
    QVector<double> spalte;
    if(spaltenindex >= this->spaltenzahl()){
        debug("Spaltenindex Überlauf!");
        return spalte;
    }
    for(int i = 0; i < this->zeilenzahl(); i++){
        spalte.append(this->get_wert(i, spaltenindex));
    }
    return spalte;
}
void matrizen::set_spalte(QVector<double> spalte, int spaltenindex){
    if(spaltenindex >= this->spaltenzahl()){
        debug("Spaltenindex Überlauf! konnte nicht gesetzt werden");
        return;
    }
    for(int i = 0; i < this->zeilenzahl(); i++){
        this->set_wert(spalte.at(i), i, spaltenindex);
    }

}
QVector<double> matrizen::get_zeile(int zeilenindex) const {
    QVector<double> zeile;
    if(zeilenindex >= this->zeilenzahl()){
        debug("Zeilenindex Überlauf!");
        return zeile;
    }
    for(int i = 0; i < this->spaltenzahl(); i++){
        zeile.append(this->get_wert(i, zeilenindex));
    }
    return zeile;
}
void matrizen::set_zeile(QVector<double> zeile, int zeilenindex){
    if(zeilenindex >= this->zeilenzahl()){
        debug("Zeilenindex Überlauf! konnte nicht gesetzt werden");
        return;
    }
    for(int i = 0; i < this->spaltenzahl(); i++){
        this->set_wert(zeile.at(i), zeilenindex, i);
    }
}
void matrizen::spaltentausch(int x, int y){
    QVector<double> spalte1 = this->get_spalte(x);
    QVector<double> spalte2 = this->get_spalte(y);
    this->set_spalte(spalte2, x);
    this->set_spalte(spalte1, y);
}
void matrizen::zeilentausch(int x, int y){
    QVector<double> zeile1 = this->get_zeile(x);
    QVector<double> zeile2 = this->get_zeile(y);
    this->set_zeile(zeile2, x);
    this->set_zeile(zeile1, y);
}
void matrizen::zeileMult(int zeilenindex, double multiplikator){
    QVector<double> zeile = this->get_zeile(zeilenindex);
    QVector<double> zeileNeu;
    foreach(double x, zeile){
        zeileNeu.append(x * multiplikator);
    }
    this->set_zeile(zeileNeu, zeilenindex);
}
void matrizen::zeileMultAdd(int veränderndeZeile, int addierendeZeile, double multiplikator){
    QVector<double> zeileVerändert = this->get_zeile(veränderndeZeile);
    QVector<double> zeileAddieren = this->get_zeile(addierendeZeile);
    for(int i = 0; i < zeileVerändert.count(); i++){
        zeileVerändert[i] += (zeileAddieren.at(i) * multiplikator);
    }
    this->set_zeile(zeileVerändert, veränderndeZeile);

}
void matrizen::print() const {
    QString text = "";
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            text += QString::number(this->get_wert(zeilenzahl, spaltenzahl));
        }
        text += "\n";
    }
    debug(text);
}
bool matrizen::isSquare() const {
    if(this->zeilenzahl() == this->spaltenzahl()){
        return true;
    }else{
        return false;
    }
}
void matrizen::toIdentity(){
    if(this->isSquare()){
        for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
            for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
                if(zeilenzahl == spaltenzahl){
                    this->set_wert(1, zeilenzahl, spaltenzahl);
                }else{
                    this->set_wert(0, zeilenzahl, spaltenzahl);
                }

            }
        }
    }else{
        debug("aus einer nicht quadratischen Matrix kann keine Einheitsmatrix gebildet werden");
    }
}
