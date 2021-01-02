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
        zeile.append(this->get_wert(zeilenindex, i));
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
void matrizen::zeileMultAdd(int veraenderndeZeile, int addierendeZeile, double multiplikator){
    QVector<double> zeileVeraendert = this->get_zeile(veraenderndeZeile);
    QVector<double> zeileAddieren = this->get_zeile(addierendeZeile);
    for(int i = 0; i < zeileVeraendert.count(); i++){
        zeileVeraendert[i] += (zeileAddieren.at(i) * multiplikator);
    }
    this->set_zeile(zeileVeraendert, veraenderndeZeile);

}
void matrizen::print() const {
    QString text = "";
    for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
        for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){

            text += QString::number(this->get_wert(zeilenzahl, spaltenzahl)) + " ";
        }
        debug(text);
        text = "";
    }

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
double matrizen::det() const {
    double det = 0;


    if(!this->isSquare()){
        debug("aus einer nich quadratischen Matrix kann keine Determinante berechnet werden");
        return 0;
    }
    if(this->zeilenzahl() == 2){//Base Case
        det = ((this->get_wert(0,0)*this->get_wert(1,1))-(this->get_wert(0,1)*this->get_wert(1,0)));
        return det;
    }else{
        int vorzeichen = 1;

        for(int index = 0; index < this->zeilenzahl(); index++){
            matrizen kopie(this->zeilenzahl(), this->spaltenzahl());
            kopie.copy(this);
            kopie.zeileLoeschen(0);
            kopie.spalteLoeschen(index);
            det += vorzeichen * this->get_wert(0, index) * kopie.det();
            vorzeichen *= -1;
        }
    }
    return det;
}
void matrizen::zeileLoeschen(int zeilenindex){
    this->matrix.remove(zeilenindex);
}
void matrizen::spalteLoeschen(int spaltenindex){
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        this->matrix[zeilenindex].remove(spaltenindex);
    }
}
void matrizen::copy(const matrizen* x){
    if(this->zeilenzahl() != x->zeilenzahl() || this->spaltenzahl() != x->spaltenzahl()){
        debug("Matrizen haben nich die gleichen Dimensionen");
        return;
    }
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            this->set_wert(x->get_wert(zeilenzahl, spaltenzahl), zeilenzahl, spaltenzahl);
        }
    }

}
void matrizen::transponieren(){




}
void matrizen::resize(int zeilenanzahl, int spaltenanzahl){
    while(this->zeilenzahl() > zeilenanzahl){
        this->matrix.erase(this->matrix.end()-1);
    }
    while(this->spaltenzahl() > spaltenanzahl){
      for(int i = 0; i < this->zeilenzahl(); i++){
          this->matrix[i].erase(this->matrix[i].end()-1);
      }
    }
    QVector<double> zeile;
    for(int i = 0; i < this->spaltenzahl(); i++){
        zeile.append(0);
    }
    while(this->zeilenzahl() < zeilenanzahl){
        this->matrix.append(zeile);
    }
    while(this->spaltenzahl() < spaltenanzahl){
        for(int i = 0; i < this->zeilenzahl(); i++){
            this->matrix[i].append(0);
        }
    }
}
void matrizen::nullen(){
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            this->set_wert(0, zeilenzahl, spaltenzahl);
        }
    }
}
