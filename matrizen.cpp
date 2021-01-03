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
    if(this->matrix.empty()){
        return 0;
    }else{
        return this->matrix.at(0).count();
    }

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
    if(x == y){
        return;
    }
    QVector<double> spalte1 = this->get_spalte(x);
    QVector<double> spalte2 = this->get_spalte(y);
    this->set_spalte(spalte2, x);
    this->set_spalte(spalte1, y);
}
void matrizen::zeilentausch(int x, int y){
    if(x == y){
        return;
    }
    QVector<double> zeile1 = this->get_zeile(x);
    QVector<double> zeile2 = this->get_zeile(y);
    this->set_zeile(zeile2, x);
    this->set_zeile(zeile1, y);
    //    debug("tausche Zeile: " + QString::number(x) + " mit Zeile: " + QString::number(y));
    //    this->print();

}
void matrizen::zeileMult(int zeilenindex, double multiplikator){
    if(multiplikator == 1){

    }
    QVector<double> zeile = this->get_zeile(zeilenindex);
    QVector<double> zeileNeu;
    foreach(double x, zeile){
        zeileNeu.append(x * multiplikator);
    }
    this->set_zeile(zeileNeu, zeilenindex);
    //    debug("multipliziere Zeile: " + QString::number(zeilenindex) + " mit " +QString::number(multiplikator));
    //    this->print();
}
void matrizen::zeileMultAdd(int veraenderndeZeile, int addierendeZeile, double multiplikator){
    QVector<double> zeileVeraendert = this->get_zeile(veraenderndeZeile);
    QVector<double> zeileAddieren = this->get_zeile(addierendeZeile);
    for(int i = 0; i < zeileVeraendert.count(); i++){
        zeileVeraendert[i] += (zeileAddieren.at(i) * multiplikator);
    }
    this->set_zeile(zeileVeraendert, veraenderndeZeile);
    //debug("multipliziere Zeile: " + QString::number(addierendeZeile) + " mit: " +
    //      QString::number(multiplikator) + " und addiere es auf Zeile: " +
    //      QString::number(veraenderndeZeile));
    //this->print();
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
    matrizen kopie(this->zeilenzahl(), this->spaltenzahl());
    kopie.copy(this);
    this->resize(this->spaltenzahl(), this->zeilenzahl());
    this->nullen();
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            this->set_wert(kopie.get_wert(spaltenzahl, zeilenzahl), zeilenzahl, spaltenzahl);
        }
    }

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
void matrizen::join(matrizen x){
    if(this->zeilenzahl() != x.zeilenzahl()){
        debug("Join geht nicht. haben nicht die gleiche Zeilenanzahl");
        return;
    }
    for(int i = 0; i < this->zeilenzahl(); i++){
        this->matrix[i].append(x.get_zeile(i));
    }
}
void matrizen::seperate(){
    if(this->spaltenzahl() != 2*this->zeilenzahl()){
        debug("geht net!");
        return;
    }
    while(this->zeilenzahl() != this->spaltenzahl()){
        this->spalteLoeschen(0);
    }
}
int matrizen::findeZeilemitMax(int spaltenindex, int startZeilenIndex) const {
    int index = -1;
    double temp = INFINITY;
    temp *= -1;
    for(int i = startZeilenIndex; i < this->zeilenzahl(); i++){
        double wert = this->get_wert(i, spaltenindex);
        wert = abs(wert);
        if(wert > temp){
            temp = wert;
            index = i;
        }
    }
    return index;
}
bool matrizen::istUngefaehrGleich(matrizen x, int genauigkeit = pow(10, -6)) const {
    if(this->zeilenzahl() != x.zeilenzahl() || this->spaltenzahl() != x.spaltenzahl()){
        debug("kann man nicht vergleichen");
        return false;
    }
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            double wert1 = this->get_wert(zeilenzahl, spaltenzahl);
            double wert2 = x.get_wert(zeilenzahl, spaltenzahl);
            double differenz = wert1 - wert2;
            differenz = abs(differenz);
            if(differenz > genauigkeit){
                return false;
            }
        }
    }
    return true;
}
void matrizen::inverse(){
    if(!this->isSquare()){
        debug("Inverse geht nur für quadratische Matrizen");
        return;
    }
    if(this->det() == 0){
        debug("Inverse geht nur für Matrizen deren det != 0 ist");
        return;
    }
    int zeilenindex = -1;
    int spaltenindex = -1;
    matrizen startmatrix(this->zeilenzahl(), this->spaltenzahl());
    startmatrix.copy(this);
    matrizen einheitsmatrix(this->zeilenzahl(), this->spaltenzahl());
    einheitsmatrix.toIdentity();
    this->join(einheitsmatrix);

    int diagonalerIndex = 0;
    bool fertig = false;
    int Iteration = 0;
    int maxIteration = 10;
    while(!fertig && Iteration < maxIteration){
        while(diagonalerIndex < this->zeilenzahl()){
            zeilenindex = diagonalerIndex;
            spaltenindex = diagonalerIndex;
            int zeileMitMax = this->findeZeilemitMax(spaltenindex, zeilenindex);

            this->zeilentausch(zeileMitMax, zeilenindex);



            this->zeileMult(zeilenindex, (1.0/this->get_wert(zeilenindex, spaltenindex)));


            this->spaltenalgorithmus(zeilenindex, spaltenindex);
            this->zeilenalgorithmus(zeilenindex, spaltenindex);

            diagonalerIndex++;
        }
        matrizen inverse(this->zeilenzahl(), this->spaltenzahl());
        inverse.copy(this);
        inverse.seperate();

        if(inverse.istUngefaehrGleich(einheitsmatrix)){
            fertig = true;
        }else{
            Iteration++;
            diagonalerIndex = 0;
        }

    }
    this->seperate();

}
void matrizen::spaltenalgorithmus(int zeilenindex, int spaltenindex){
    zeilenindex++;
    while(zeilenindex < this->zeilenzahl()){
        if(istUngefaehrgleich(this->get_wert(zeilenindex, spaltenindex),0)){//vllt ein close to statt ein ==
            zeilenindex++;
        }else{
            int ersteZeileIndex = spaltenindex;
            double ersteZeileWert = this->get_wert(ersteZeileIndex, spaltenindex);
            if(istUngefaehrgleich(ersteZeileWert, 0)){//vllt ein close to statt ein ==
                zeilenindex++;
            }else{
                double aktuellerWert = this->get_wert(zeilenindex, spaltenindex);
                double mult = -(aktuellerWert/ersteZeileWert);
                this->zeileMultAdd(zeilenindex, ersteZeileIndex, mult);
                zeilenindex++;
            }
        }
    }
}
void matrizen::zeilenalgorithmus(int zeilenindex, int spaltenindex){
    spaltenindex++;
    while(spaltenindex < this->zeilenzahl()){
        if(istUngefaehrgleich(this->get_wert(zeilenindex, spaltenindex),0)){//vllt ein close to statt ein ==
            spaltenindex++;
        }else{
            int ersteZeileindex = spaltenindex;
            double ersteZeileWert = this->get_wert(ersteZeileindex, spaltenindex);
            if(istUngefaehrgleich(ersteZeileWert, 0)){//vllt ein close to statt ein ==
                spaltenindex++;
            }else{
                double aktuellerWert = this->get_wert(zeilenindex, spaltenindex);
                double mult = -(aktuellerWert/ersteZeileWert);
                this->zeileMultAdd(zeilenindex, ersteZeileindex, mult);
                spaltenindex++;
            }
        }
    }
}
matrizen matrizen::operator*(matrizen x) const {
    matrizen erg;
    if(this->spaltenzahl() != x.zeilenzahl()){
        debug("MatrixMultiplikation geht net. falsche Dimensionen");
        return erg;
    }
    erg.resize(this->zeilenzahl(), x.spaltenzahl());
    for(int zeilenindex = 0; zeilenindex < erg.zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < erg.spaltenzahl(); spaltenindex++){
            double wert = 0;
            for(int i = 0; i < x.zeilenzahl(); i++){
                wert += this->get_wert(zeilenindex, i) * x.get_wert(i, spaltenindex);
            }
            erg.set_wert(wert, zeilenindex, spaltenindex);
        }
    }
    return erg;
}
bool istUngefaehrgleich(double z1, double z2, double genauigkeit){
    if(abs(z1-z2)<genauigkeit){
        return true;
    }else{
        return false;
    }
}
matrizen matrizen::operator+(matrizen x) const {
    matrizen erg(this->zeilenzahl(), this->spaltenzahl());
    if(this->zeilenzahl() != x.zeilenzahl() || this->spaltenzahl() != x.spaltenzahl()){
        return matrizen();
    }
    for(int zeilenindex = 0; zeilenindex < erg.zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < erg.spaltenzahl(); spaltenindex++){
            erg.set_wert(x.get_wert(zeilenindex, spaltenindex) + this->get_wert(zeilenindex, spaltenindex), zeilenindex, spaltenindex);
        }
    }
    return erg;
}
matrizen matrizen::operator-(matrizen x) const {
    matrizen erg(this->zeilenzahl(), this->spaltenzahl());
    if(this->zeilenzahl() != x.zeilenzahl() || this->spaltenzahl() != x.spaltenzahl()){
        return matrizen();
    }
    x = x * -1;
    erg = *this + x;
    return erg;
}
matrizen matrizen::operator*(double d)const {
    matrizen erg(this->zeilenzahl(), this->spaltenzahl());
    for(int zeilenindex = 0; zeilenindex < erg.zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < erg.spaltenzahl(); spaltenindex++){
            erg.set_wert(d * this->get_wert(zeilenindex, spaltenindex), zeilenindex, spaltenindex);
        }
    }
    return erg;
}
void matrizen::gauss(){
    /*
    if(this->spaltenzahl() - 1 != this->zeilenzahl()){
        debug("gauß macht keinen Sinn");
        return;
    }
    */
    int diagonalIndex = 0;
    for(int spaltenindex = 0; spaltenindex < this->zeilenzahl(); spaltenindex++){
        int i = 0;
        while(this->get_wert(diagonalIndex, diagonalIndex) == 0 && i < this->zeilenzahl()){
            this->zeilentausch(diagonalIndex, i);
            i++;
        }//Jetzt sollte keine null mehr in der Hauptdiagonalen stehen
        for(int j = 0; j < diagonalIndex; j++){
            this->zeileMultAdd(diagonalIndex, j, -this->get_wert(diagonalIndex, j));
        }
        double wert = this->get_wert(diagonalIndex, diagonalIndex);
        if(wert != 0){
            this->zeileMult(diagonalIndex, 1.0/this->get_wert(diagonalIndex, diagonalIndex));
        }

        diagonalIndex++;

    }

    for(int i = 0; i < this->zeilenzahl(); i++){
        int counter = i + 1;
        while(this->get_wert(i,i) == 0 && counter<this->zeilenzahl()){
            this->zeilentausch(i,counter);
            counter++;
        }
    }
    for(int i = 0; i < this->zeilenzahl(); i++){
        if(this->get_wert(i,i) != 0){
            this->zeileMult(i, 1.0/this->get_wert(i,i));
        }
    }

}
int matrizen::rang() const {
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    x.nullZeilenLoeschen();
    if(x.zeilenzahl() == 0){
        return 0;
    }
    if(x.zeilenzahl() == 1){
        return 1;
    }
    if(x.spaltenzahl() == 1){
        return 1;
    }
    x.gauss();
    x.nullZeilenLoeschen();
    int rang = x.zeilenzahl();
    for(int i = 0; i < x.zeilenzahl(); i++){
        int j = i + 1;
        while(j < x.zeilenzahl()){
            if(x.linearAbhaengig(i, j)){
                rang--;
            }
            j++;
        }
    }
    return rang;
}
bool matrizen::linearAbhaengig(int x, int y) const {
    double factor;
    bool factorGefunden = false;
    auto zeileX = this->get_zeile(x);
    auto zeileY = this->get_zeile(y);
    for(int i = 0; i < zeileX.count(); i++){
        if(zeileX.at(i) != 0){
            factor = zeileY.at(i) / zeileX.at(i);
            factorGefunden = true;
            break;
        }
    }
    if(factorGefunden){
        for(int i = 0; i < zeileX.count(); i++){
            if(!istUngefaehrgleich(zeileX.at(i) * factor, zeileY.at(i))){
                return false;
            }
        }
        return true;
    }
    for(int i = 0; i < zeileX.count(); i++){
        if(zeileY.at(i) != 0){
            factor = zeileX.at(i) / zeileY.at(i);
            factorGefunden = true;
            break;
        }
    }
    if(factorGefunden){
        for(int i = 0; i < zeileX.count(); i++){
            if(!istUngefaehrgleich(zeileY.at(i) * factor, zeileX.at(i))){
                return false;
            }
        }
        return true;
    }
    return true;//wenn sie hier angekommen sind, dann müssen beide zeilen Nullzeilen sein
}
bool matrizen::nullZeile(int zeilenindex) const {
    auto zeile = this->get_zeile(zeilenindex);
    foreach(auto x, zeile){
        if(!istUngefaehrgleich(0, x)){
            return false;
        }
    }
    return true;
}
void matrizen::nullZeilenLoeschen(){
    int i = 0;
    while(i < this->zeilenzahl()){
        if(this->nullZeile(i)){
            this->zeileLoeschen(i);
        }
        i++;
    }
}
bool matrizen::diagonalMatrix() const {
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < this->spaltenzahl(); spaltenindex++){
            if(zeilenindex != spaltenindex && this->get_wert(zeilenindex, spaltenindex) != 0){
                return false;
            }
        }
    }
    return true;
}
bool matrizen::obereDreiecksMatrix() const {
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < this->spaltenzahl(); spaltenindex++){
            if(zeilenindex > spaltenindex && this->get_wert(zeilenindex, spaltenindex) != 0){
                return false;
            }
        }
    }
    return true;
}
bool matrizen::einheitsMatrix() const {
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < this->spaltenzahl(); spaltenindex++){
            if(zeilenindex == spaltenindex && this->get_wert(zeilenindex, spaltenindex) != 1){
                return false;
            }
            if(zeilenindex != spaltenindex && this->get_wert(zeilenindex, spaltenindex) != 0){
                return false;
            }
        }
    }
    return true;
}
bool matrizen::nullMatrix() const {
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < this->spaltenzahl(); spaltenindex++){
            if(this->get_wert(zeilenindex, spaltenindex) != 0){
                return false;
            }
        }
    }
    return true;
}
bool matrizen::einsMatrix() const {
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < this->spaltenzahl(); spaltenindex++){
            if(this->get_wert(zeilenindex, spaltenindex) != 1){
                return false;
            }
        }
    }
    return true;
}
bool matrizen::symetrischeMatrix() const {
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    x.transponieren();
    return (this->istUngefaehrGleich(x));
}
bool matrizen::schiefsymetrischeMatrix() const {
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    matrizen y(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    y.copy(this);
    x.transponieren();
    y = y *-1;
    return y.istUngefaehrGleich(x);
}
bool matrizen::orthogonnaleMatrix() const {
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    matrizen y(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    y.copy(this);
    x.transponieren();
    y = x * y;
    x.toIdentity();
    return y.istUngefaehrGleich(x);
}
bool matrizen::idempotenteMatrix() const {
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    return x.istUngefaehrGleich(x*x);
}
int matrizen::spur() const {
    if(this->isSquare()){
        double erg = 0;
        for(int i = 0; i < this->zeilenzahl(); i++){
            erg += this->get_wert(i, i);
        }
        return erg;
    }
    debug("Matrix nicht Quadratisch. Spurberechnung nicht möglich");
    return 0;
}
