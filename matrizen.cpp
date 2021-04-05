#include "matrizen.h"



matrizen::matrizen()
{

}
matrizen::matrizen(int zeilenzahl, int spaltenzahl){
    //erstellt eine Matrix mit der Zeilen- und Spaltenzahl
    //dabei sind alle Elemente null
    QVector<double> spalte;
    for(int i = 0; i < spaltenzahl; i++){
        spalte.append(0);
    }
    for(int i = 0; i < zeilenzahl; i++){
        this->matrix.append(spalte);
    }
}
matrizen::matrizen(const matrizen* x){
    //der Kopierkonstruktor
    //erstllt eine Matrix die genau die gleichen Eigenschaften hat wie die die übergeben wurde
    this->matrix = x->matrix;
}
double matrizen::get_wert(int zeilenzahl, int spaltenzahl) const {
    //gibt den Wert an einer bestimmten Position zurück
    return this->matrix.at(zeilenzahl).at(spaltenzahl);
}
void matrizen::set_wert(double wert, int zeilenzahl, int spaltenzahl){
    //setzt den Wert an einer bestimmten Position
    this->matrix[zeilenzahl][spaltenzahl] = wert;
}
int matrizen::zeilenzahl() const {
    //gibt die Anzahl an Zeilen zurück
    return this->matrix.count();
}
int matrizen::spaltenzahl() const {
    //gibt die Anzahl an Spalten zurück
    if(this->matrix.empty()){
        return 0;
    }else{
        return this->matrix.at(0).count();
    }

}
matrizen matrizen::get_spalte(int spaltenindex) const {
    //gibt die Spalte als Spaltenvektor zurück
    matrizen spalte(this->zeilenzahl(), 1);
    if(spaltenindex >= this->spaltenzahl()){
        debug("Spaltenindex Überlauf!");
        return matrizen();
    }
    for(int i = 0; i < this->zeilenzahl(); i++){
        spalte.set_wert(this->get_wert(i, spaltenindex), i, 0);
    }
    return spalte;
}
void matrizen::set_spalte(matrizen spalte, int spaltenindex){
    //bekommt einen Spaltenvektor und setzt ihn auf die gewünschte Spalte in der Matrix
    if(spaltenindex >= this->spaltenzahl()){
        debug("Spaltenindex Überlauf! konnte nicht gesetzt werden");
        return;
    }
    if(spalte.spaltenzahl() != 1){
        debug("Set_Spalte geht nicht.Ist kein Spaltenvektor");
        return;
    }
    for(int i = 0; i < this->zeilenzahl(); i++){
        this->set_wert(spalte.get_wert(i,0), i, spaltenindex);
    }

}
matrizen matrizen::get_zeile(int zeilenindex) const {
    //gibt die Spalte als Zeilenvektor zurück
    matrizen zeile(1, this->spaltenzahl());
    if(zeilenindex >= this->zeilenzahl()){
        debug("Zeilenindex Überlauf!");
        return matrizen();
    }
    for(int i = 0; i < this->spaltenzahl(); i++){
        zeile.set_wert(this->get_wert(zeilenindex, i), 0, i);
    }
    return zeile;
}
void matrizen::set_zeile(matrizen zeile, int zeilenindex){
    //bekommt einen Zeilenvektor und setzt ihn auf die gewünschte Zeile in der Matrix
    if(zeilenindex >= this->zeilenzahl()){
        debug("Zeilenindex Überlauf! konnte nicht gesetzt werden");
        return;
    }
    if(zeile.zeilenzahl() != 1){
        debug("Set_Zeile geht nicht.Ist kein Zeilenvektor");
        return;
    }
    for(int i = 0; i < this->spaltenzahl(); i++){
        this->set_wert(zeile.get_wert(0, i), zeilenindex, i);
    }
}
void matrizen::spaltentausch(int x, int y){
    //tauscht zwei Spalten
    if(x == y){
        return;
    }
    auto spalte1 = this->get_spalte(x);
    auto spalte2 = this->get_spalte(y);
    this->set_spalte(spalte2, x);
    this->set_spalte(spalte1, y);
}
void matrizen::zeilentausch(int x, int y){
    //tauscht zwei Zeilen
    if(x == y){
        return;
    }
    auto zeile1 = this->get_zeile(x);
    auto zeile2 = this->get_zeile(y);
    this->set_zeile(zeile2, x);
    this->set_zeile(zeile1, y);
    //    debug("tausche Zeile: " + QString::number(x) + " mit Zeile: " + QString::number(y));
    //    this->print();

}
void matrizen::zeileMult(int zeilenindex, double multiplikator){
    //multipliziert eine Zeile mit einem Wert
    if(multiplikator == 1){
        return;
    }
    matrizen zeile = this->get_zeile(zeilenindex);
    matrizen zeileNeu(1, this->spaltenzahl());
    for(int i = 0; i < zeile.spaltenzahl(); i++){
        zeileNeu.set_wert(zeile.get_wert(0, i) * multiplikator, 0, i);
    }
    this->set_zeile(zeileNeu, zeilenindex);
    //    debug("multipliziere Zeile: " + QString::number(zeilenindex) + " mit " +QString::number(multiplikator));
    //    this->print();
}
void matrizen::zeileMultAdd(int veraenderndeZeile, int addierendeZeile, double multiplikator){
    //multipliziert eine Zeile und addiert sie auf eine andere drauf
    auto zeileVeraendert = this->get_zeile(veraenderndeZeile);
    auto zeileAddieren = this->get_zeile(addierendeZeile);
    for(int i = 0; i < zeileVeraendert.spaltenzahl(); i++){
        //zeileVeraendert[i] += (zeileAddieren.at(i) * multiplikator);
        double wert = zeileVeraendert.get_wert(0,i) + multiplikator * zeileAddieren.get_wert(0, i);
        zeileVeraendert.set_wert(wert,0, i);
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
    //überprüft, ob die Matrix quadratisch ist
    if(this->zeilenzahl() == this->spaltenzahl()){
        return true;
    }else{
        return false;
    }
}
void matrizen::toIdentity(){
    //wandelt eine Matrix in die Einhetismatrix um
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
    //Berechnet die Determinante der Matrix
    //Wenn die Matrix eine 1x1 Matrix ist, dann ist die Determinante gleich dem einzigen Element
    //Wenn sie größer ist, dann wird der Laplacesche Entwicklungssatz verwendet
    //und durch Rekursion auf eine 1x1 matrix zurückgeführt
    double det = 0;

    if(!this->isSquare()){
        debug("aus einer nich quadratischen Matrix kann keine Determinante berechnet werden");
        return 0;
    }
    if(this->zeilenzahl() == 1){//Base Case
        return this->get_wert(0,0);
    }else{
        int vorzeichen = 1;

        for(int index = 0; index < this->zeilenzahl(); index++){
            matrizen kopie(this);//Matrix wird kopiert
            kopie.zeileLoeschen(0);//erste Zeile wird weggeschnitten
            kopie.spalteLoeschen(index);//und die n-nte Spalte
            //Die Determinante ist dann der Wert in der ersten Zeile und der n-ten Spalte
            //mal die Determinante von kopie mal das vorzeichen
            //und das plus die nächste Determinante
            det += vorzeichen * this->get_wert(0, index) * kopie.det();
            vorzeichen *= -1;//alternierendes Vorzeichen
        }
    }
    return det;
}
void matrizen::zeileLoeschen(int zeilenindex){
    //löscht eine Zeile
    this->matrix.remove(zeilenindex);
}
void matrizen::spalteLoeschen(int spaltenindex){
    //löscht eine Spalte
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        this->matrix[zeilenindex].remove(spaltenindex);
    }
}
void matrizen::copy(const matrizen* x){
    //kopiert eine Matrix in diese Matrix
    //mit dem Kopierkonstruktor wird diese Methode eig nicht mehr gebraucht
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
    //transponiert eine Matrix
    matrizen kopie(this);
    this->resize(this->spaltenzahl(), this->zeilenzahl());
    this->nullen();
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            this->set_wert(kopie.get_wert(spaltenzahl, zeilenzahl), zeilenzahl, spaltenzahl);
        }
    }

}
void matrizen::resize(int zeilenanzahl, int spaltenanzahl){
    //nimmt diese Matrix und bringt sie auf ein neues Format
    while(this->zeilenzahl() > zeilenanzahl){//Wenn Zeilen zu viel sind, werden die letzten gelöscht
        this->matrix.erase(this->matrix.end()-1);
    }
    while(this->spaltenzahl() > spaltenanzahl){//Wenn Spalten zu viel sind, werden die letzen gelöscht
        for(int i = 0; i < this->zeilenzahl(); i++){
            this->matrix[i].erase(this->matrix[i].end()-1);
        }
    }
    QVector<double> zeile;
    for(int i = 0; i < this->spaltenzahl(); i++){//eine Nullzeile mit der gewünschten Spaltenzahl wird erstellt
        zeile.append(0);
    }
    while(this->zeilenzahl() < zeilenanzahl){//wenn Zeilen zu wenig sind, dann werden Nullzeilen hinzugefügt
        this->matrix.append(zeile);
    }
    while(this->spaltenzahl() < spaltenanzahl){//Wenn Spalten zu wenig sind, dann werden Nullspalten hinzugefügt
        for(int i = 0; i < this->zeilenzahl(); i++){
            this->matrix[i].append(0);
        }
    }
}
void matrizen::nullen(){
    //ersetzt jedes Element der Matrix durch nullen
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            this->set_wert(0, zeilenzahl, spaltenzahl);
        }
    }
}
void matrizen::join(matrizen x){
    //verbindet zwei Matrizen spaltenweise
    if(this->zeilenzahl() != x.zeilenzahl()){//deshalb brauchen sie die gleiche Zeilenzahl
        debug("Join geht nicht. haben nicht die gleiche Zeilenanzahl");
        return;
    }
    const int originalMaxSpaltenindex = this->spaltenzahl();
    this->resize(this->zeilenzahl(), this->spaltenzahl()+x.spaltenzahl());

    for(int i = 0; i < x.zeilenzahl(); i++){
        auto spalte = x.get_spalte(i);
        this->set_spalte(spalte, originalMaxSpaltenindex+i);
    }
}
void matrizen::seperate(){
    //Wenn zwei quadratische Matrizen zusammengefügt worden sind, dann wird hier die vordere Matrize abgeschnitten
    if(this->spaltenzahl() != 2*this->zeilenzahl()){//deshalb muss die Matrize doppelt so viele Spalten wie Zeilen haben
        debug("geht net!");
        return;
    }
    while(this->zeilenzahl() != this->spaltenzahl()){
        this->spalteLoeschen(0);
    }
}
int matrizen::findeZeilemitMax(int spaltenindex, int startZeilenIndex) const {
    //findet die Zeile mit dem größten Absolutwert, die unter der startZeile ist, innerhab einer Spalte
    int index = NAN;
    double temp = -INFINITY;
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
    //zwei Matrizen sind gleich, wenn die absolute Differenz Elementenweise überall kleiner ist als genauigkeit
    if(this->zeilenzahl() != x.zeilenzahl() || this->spaltenzahl() != x.spaltenzahl()){
        debug("kann man nicht vergleichen");
        return false;
    }
    for(int spaltenzahl = 0; spaltenzahl < this->spaltenzahl(); spaltenzahl++){
        for(int zeilenzahl = 0; zeilenzahl < this->zeilenzahl(); zeilenzahl++){
            double wert1 = this->get_wert(zeilenzahl, spaltenzahl);
            double wert2 = x.get_wert(zeilenzahl, spaltenzahl);
            double differenz = wert1 * double(1000000) - wert2 * double(1000000);
            differenz = abs(differenz);
            if(differenz > (genauigkeit * double(1000000))){
                return false;
            }
        }
    }
    return true;
}
void matrizen::inverse(){
    //Invertierung einer Matrix nach dem Gauß-Jordan Verfahren
    //grobes Prinzip:
    //Die Einheitsmatrix wird neben dran geschrieben
    //es dürfen nur Zeilen getauscht, Zeilen mit einer Konstante (!=0) multipliziert und Zeilen addiert werden
    //das Ziel ist es am Ende die Einheitsmatrix auf der linken Seite zu bekommen, dann ist rechts die Inverse

    if(!this->isSquare()){//eine Matrix kann man nur invertieren wenn sie Quadratisch
        debug("Inverse geht nur für quadratische Matrizen");
        return;
    }
    if(this->det() == 0){//und ihre Determinante ungleich 0 ist
        debug("Inverse geht nur für Matrizen deren det != 0 ist");
        return;
    }
    matrizen startmatrix(this);//Speichert die Matrix ab
    matrizen einheitsmatrix(this);
    einheitsmatrix.toIdentity();//generiert eine Einheitsmatrix mit den gleichen Dimenionen
    const int maxZeile = this->zeilenzahl();//eine Konstante die die Anzahl an zeilen beinhaltet
    this->join(einheitsmatrix);//verbindet diese Matrix mit der Einheitsmatrix

    for(int diagIndex = 0; diagIndex < maxZeile; diagIndex++){//es wird durch jede Zeile gegangen
        int i = diagIndex + 1;//i ist ein Index der in der darauffolgenden Zeile startet
        double pivotelement = this->get_wert(diagIndex, diagIndex);//das ist das Element in dieser Zeile in der Hauptdiagonalen
        while(istUngefaehrgleich(pivotelement, 0) && i < maxZeile){//solange dieses Element = 0 ist und i kleiner ist als die maximale Zeilenzahl
            this->zeilentausch(i, diagIndex);//Zeile wird getauscht
            pivotelement = this->get_wert(diagIndex, diagIndex);//da Zeile getauscht wurde, gibt es jetzt auch ein neues pivotelement
            i++;//Index wird erhöht. falls das Pivotelement wieder null sein sollte wird die übernächdte Zeile genommen etc
        }//versucht das Pivotelement ungleich von Null zu machen
        //jetzt sollte das Pivotelement != 0 sein aber es wird nochmal auf nummer sicher gegangen
        if(!istUngefaehrgleich(pivotelement, 0)){
            this->zeileMult(diagIndex, 1.0/pivotelement);//Zeile wird so multipliziert das das Pivotelement 1 wird
        }
        for(int zeilenIndex = 0; zeilenIndex < maxZeile; zeilenIndex++){//es wird über alle Zeilen Iteriert
            if(diagIndex != zeilenIndex){//die Zeile in der wir gerade sind wird ausgelassen
                double element = this->get_wert(zeilenIndex, diagIndex);//das element in der gleichen Spalte wie das Pivotelement
                if(!istUngefaehrgleich(0, element)){//wenn diess Element nicht 0 ist
                    double mult = -element;
                    this->zeileMultAdd(zeilenIndex, diagIndex, mult);//dann wird die zeile mit dem Pivotelement so multipliziert und auf die andere Zeile addiert, dass das element 0 wird
                }
            }
        }//jetzt sollten alle Elemente in dieser Spalte außer das Pivotelement null sein
    }//das wird für alle Spalten gemacht
    //jetzt solle links die Einheitsmatrix und rechts die inverse sein
    this->seperate();

    /*
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
    */

}
void matrizen::spaltenalgorithmus(int zeilenindex, int spaltenindex){
    //wurde für ein anderes Verfahren gebraucht
    //ist jetzt eig überflüssig
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
    //wurde für ein anderes Verfahren gebraucht
    //ist jetzt eig überflüssig
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
    //zwei Matrizen werden multipliziert
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
    //schaut ob zwei Zahlen innerhalb einer Toleranz gleich sind
    if(abs(z1-z2)<genauigkeit){
        return true;
    }else{
        return false;
    }
}
matrizen matrizen::operator+(matrizen x) const {
    //addiert zwei Matrizen
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
    //subtrahiert zwei Matrizen
    matrizen erg(this->zeilenzahl(), this->spaltenzahl());
    if(this->zeilenzahl() != x.zeilenzahl() || this->spaltenzahl() != x.spaltenzahl()){
        return matrizen();
    }
    x = x * -1;
    erg = *this + x;
    return erg;
}
matrizen matrizen::operator*(double d)const {
    //multipliziert eine Matrix mit einer Konstanten
    matrizen erg(this->zeilenzahl(), this->spaltenzahl());
    for(int zeilenindex = 0; zeilenindex < erg.zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < erg.spaltenzahl(); spaltenindex++){
            erg.set_wert(d * this->get_wert(zeilenindex, spaltenindex), zeilenindex, spaltenindex);
        }
    }
    return erg;
}
void matrizen::gauss(){
    //wendet das Gauß Verfahren an um eine obere Dreiecksmatrix zu erzeugen


    /*
    if(this->spaltenzahl() - 1 != this->zeilenzahl()){
        debug("gauß macht keinen Sinn");
        return;
    }
    */
    int counter = 1;
    while(!this->gaussform()){//solange nicht die Gaussform vorliegt
    const int maxIterationen = this->kleinsteDimension();
    for(int diagIndex = 0; diagIndex < maxIterationen; diagIndex++){//wird durch die diagonale Iteriert
        double Pivotelement = this->get_wert(diagIndex, diagIndex);//zieht sich das erste hauptdiagonalenelement
        int i = diagIndex + 1;//Zeilen sollen nur die unteren der aktuellen genommen werden
        while(istUngefaehrgleich(0, Pivotelement) && i < this->zeilenzahl()){//solange das Pivotelement null ist und noch nicht das zeilenende erreicht
            this->zeilentausch(i, diagIndex);//werden Zeilen getauscht
            Pivotelement = this->get_wert(diagIndex, diagIndex);//der neue Pivotelement wird gesetzt
            i++;//und es wird dei nächste zeile ausgewählt
            if(counter % 5 == 0){
                this->zeileMultAdd(0, diagIndex, -1);
            }
        }//Das Pivotelement solle nicht mehr null sein. Wenn es Null ist, dann wird die gaußform nicht errreicht. Deshalb die while !gaußform schleife
        if(!istUngefaehrgleich(0, Pivotelement)){//Trotzdem wird es nochmals kontrolliert
            this->zeileMult(diagIndex, 1.0/Pivotelement);//wenn es nicht null ist, dann wird die Zeile normiert
        }
        for(int j = diagIndex + 1; j < zeilenzahl(); j++){//Jetzt wird durch die unteren Zeilen durchiteriert und das Zuel ist es alles in der Pivotspalte null zu bekommen
            double element = this->get_wert(j, diagIndex);
            if(!istUngefaehrgleich(0, element)){
                this->zeileMultAdd(j, diagIndex, -element);
            }
        }
    }
    counter++;
    }
}
bool matrizen::gaussform()const{
    //Überprüft, ob die Gaußform vorliegt, also ob es eine obere Dreiecksmatrix ist
    //falls sie nicht Quadratisch ist, dann müssen alle Elemente unter der Hauptdiagonalen null sein
    const int iterationen = this->kleinsteDimension();
    bool einHauptdiagonalenelementWarSchonNull = false;
    for(int i = 0; i < iterationen; i++){
        for(int j = i; j < this->zeilenzahl(); j++){
            if(i == j){
                if(einHauptdiagonalenelementWarSchonNull){
                    if(!istUngefaehrgleich(0, this->get_wert(j,i))){
                        return false;
                    }
                }else{
                    if(istUngefaehrgleich(0, this->get_wert(j,i))){
                        einHauptdiagonalenelementWarSchonNull = true;
                    }
                }
            }else{
                if(!istUngefaehrgleich(0, this->get_wert(j, i))){
                    return false;
                }
            }
        }
    }
    return true;
}
int matrizen::rang() const {
    //bestimmt den Rang einer Matrix
    matrizen x(this);
    x.nullZeilenLoeschen();//unnötige Zeilen werden direkt gelöscht
    x.nullSpaltenLoeschen();//unnötige Spaletn werden direkt gelöscht
    if(x.zeilenzahl() == 0){//falls jetzt nix mehr da ist, wird 0 zurückgegeben
        return 0;
    }
    if(x.zeilenzahl() == 1){//oder falls nur eine Zeile
        return 1;
    }
    if(x.spaltenzahl() == 1){//oder nur eine Spalte da ist
        return 1;
    }
    x.gauss();//Gauß wird angewendet um evtl lineare Abhängigkeiten rauszufiltern
    x.nullZeilenLoeschen();
    x.nullSpaltenLoeschen();
    int rang = x.kleinsteDimension();//der Rang kann maximal die kleinste Dimension sein und Nullzeilen zählen nicht
    for(int i = 0; i < x.zeilenzahl(); i++){
        int j = i + 1;
        while(j < x.zeilenzahl()){//jetzt wird geprüft ob irgendwelche Zeilen linear Abhängig sind, falls ja, wird der Rang um 1 verringert
            if(x.linearAbhaengig(i, j)){
                rang--;
            }
            j++;
        }
    }
    return rang;
}
bool matrizen::linearAbhaengig(int x, int y) const {
    //Überprüft ob zwei Teilen linear abhängig sind. also ob zeile1 * konstante = zeile2
    //der Faktor muss natürlich ungleich 0 sein
    double factor;
    bool factorGefunden = false;
    auto zeileX = this->get_zeile(x);
    auto zeileY = this->get_zeile(y);
    for(int i = 0; i < zeileX.spaltenzahl(); i++){
        if(zeileX.get_wert(0,i) != 0){
            factor = zeileY.get_wert(0,i) / zeileX.get_wert(0,i);
            factorGefunden = true;
            break;
        }
    }
    if(factorGefunden){
        for(int i = 0; i < zeileX.spaltenzahl(); i++){
            if(!istUngefaehrgleich(zeileX.get_wert(0,i) * factor, zeileY.get_wert(0,i))){
                return false;
            }
        }
        return true;
    }
    for(int i = 0; i < zeileX.spaltenzahl(); i++){
        if(zeileY.get_wert(0,i) != 0){
            factor = zeileX.get_wert(0,i) / zeileY.get_wert(0,i);
            factorGefunden = true;
            break;
        }
    }
    if(factorGefunden){
        for(int i = 0; i < zeileX.spaltenzahl(); i++){
            if(!istUngefaehrgleich(zeileY.get_wert(0,i) * factor, zeileX.get_wert(0,i))){
                return false;
            }
        }
        return true;
    }
    return true;//wenn sie hier angekommen sind, dann müssen beide Zeilen Nullzeilen sein
}
bool matrizen::nullZeile(int zeilenindex) const {
    //überprüft ob eine Zeile null ist
    auto zeile = this->get_zeile(zeilenindex);
    for(int i = 0; i < zeile.spaltenzahl(); i++){
        double x = zeile.get_wert(0,i);
        if(!istUngefaehrgleich(0, x)){
            return false;
        }
    }
    return true;
}
bool matrizen::nullSpalte(int spaltenindex) const {
    //Überprüft ob eine Spalte null ist
    auto spalte = this->get_spalte(spaltenindex);
    for(int i = 0; i < spalte.zeilenzahl(); i++){
        double x = spalte.get_wert(i,0);
        if(!istUngefaehrgleich(0, x)){
            return false;
        }
    }
    return true;
}
void matrizen::nullZeilenLoeschen(){
    //löscht Nullzeilen
    int i = 0;
    while(i < this->zeilenzahl()){
        if(this->nullZeile(i)){
            this->zeileLoeschen(i);
        }else{
            i++;
        }
    }
}
void matrizen::nullSpaltenLoeschen(){
    //Löscht nullspalten
    int i = 0;
    while(i < this->spaltenzahl()){
        if(this->nullSpalte(i)){
            this->spalteLoeschen(i);
        }else{
            i++;
        }
    }
}
bool matrizen::diagonalMatrix() const {
    //überprüft ob es eine diagonalMatrix ist
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
    //überprüft ob es eine obere Dreiceksmatrix ist
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
    //überprüft ob es eine Nullmatrix ist
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
    //überprüft ob es eine einsMatrix ist
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
    //überprüft ob es eine Symetrische matrix ist
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    x.transponieren();
    return (this->istUngefaehrGleich(x));
}
bool matrizen::schiefsymetrischeMatrix() const {
    //überprüft ob es eine schiefsymmetrische Matrix ist
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    matrizen y(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    y.copy(this);
    x.transponieren();
    y = y *-1;
    return y.istUngefaehrGleich(x);
}
bool matrizen::orthogonnaleMatrix() const {
    //überprüft ob es eine orthogonale Matrix ist
    matrizen x(this);
    matrizen y(this);
    x.transponieren();
    y = x * y;
    x.toIdentity();
    return y.istUngefaehrGleich(x);
}
bool matrizen::idempotenteMatrix() const {
    //überprüft ob es eine Idempotente Matrix ist
    matrizen x(this->zeilenzahl(), this->spaltenzahl());
    x.copy(this);
    return x.istUngefaehrGleich(x*x);
}
int matrizen::spur() const {
    //berechnet die Spur der Matrix
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
matrizen matrizen::hadamard(matrizen x) const {
    //berechnet das hadamart Produkt zweier matrizen
    matrizen erg;
    if(this->zeilenzahl() != x.zeilenzahl() && this->spaltenzahl() != x.spaltenzahl()){
        debug("Hadamardprodukt geht nicht. falsche Dimension");
        return erg;
    }
    erg.resize(this->zeilenzahl(), this->spaltenzahl());
    for(int zeilenindex = 0; zeilenindex < this->zeilenzahl(); zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < this->spaltenzahl(); spaltenindex++){
            double wert = this->get_wert(zeilenindex, spaltenindex) * x.get_wert(zeilenindex, spaltenindex);
            erg.set_wert(wert, zeilenindex, spaltenindex);
        }
    }
    return erg;
}
QVector<komplex> matrizen::eigenwerte()const{
    //soll Eigenwerte berechnen
    //Ich würds noch nicht benutzen...
    QVector<komplex> eigenwerte;
    QVector<double> charakteristischeGleichung;
    if(!this->isSquare()){
        debug("Eigenwerte nur von quadratischen Matrizen");
        return eigenwerte;
    }
    if(this->zeilenzahl() == 1){
        charakteristischeGleichung.append(-1);
        charakteristischeGleichung.append(this->get_wert(0,0));
    }
    if(this->zeilenzahl() == 2){
        charakteristischeGleichung.append(1);
        double p = -this->get_wert(0,0) - this->get_wert(1,1);
        double q = this->get_wert(0,0) * this->get_wert(1,1) - this->get_wert(1,0) * this->get_wert(0,1);
        charakteristischeGleichung.append(p);
        charakteristischeGleichung.append(q);
    }
    if(this->zeilenzahl() == 3){

    }

    eigenwerte = PolynomHandler(charakteristischeGleichung);
    /*
    //QR Zerlegung
    if(!this->isSquare()){
        return eigenwerte;
    }
    matrizen QRZerlegungsmatrix(this);
    matrizen Inputmatrix(this);
    matrizen Q(Inputmatrix.zeilenzahl(), Inputmatrix.spaltenzahl());
    //matrizen q(Inputmatrix.zeilenzahl(), Inputmatrix.spaltenzahl());
    matrizen R(Inputmatrix.zeilenzahl(), Inputmatrix.spaltenzahl());
    matrizen vorherigeIteration(Inputmatrix.zeilenzahl(), Inputmatrix.spaltenzahl());
    R.nullen();
    int counter = 0;
    int maxCounter = 10000;
    bool weitermachen = true;
    matrizen einheitsmatrix(QRZerlegungsmatrix.zeilenzahl(), QRZerlegungsmatrix.spaltenzahl());
    einheitsmatrix.toIdentity();
    QRZerlegungsmatrix = QRZerlegungsmatrix * einheitsmatrix;
    while(weitermachen){

        for(int n = 0; n < QRZerlegungsmatrix.spaltenzahl(); n++){//Gram Schmidt Orthogonalisierung und setzt Q und R
            matrizen anSenk = QRZerlegungsmatrix.get_spalte(n);
            matrizen an = anSenk;
            for(int sum = 0; sum < n; sum++){
                matrizen q_sum = Q.get_spalte(sum);
                double sp = skalarprodukt(an, q_sum);
                anSenk = anSenk - (q_sum * (sp/q_sum.betragsquadrat()));
                R.set_wert(sp/q_sum.betragsquadrat(), sum, n);
            }
            double laenge =anSenk.betrag();
            R.set_wert(laenge, n, n);
            anSenk = anSenk * (1.0/laenge);
            Q.set_spalte(anSenk, n);
        }
        QRZerlegungsmatrix = R * Q;
        if(Q.istUngefaehrGleich(vorherigeIteration, (double) 0.0001)){
            weitermachen = false;
        }
        if(counter%20 == 0){
            matrizen();
        }
        if(!(counter < maxCounter)){
            return eigenwerte;
        }
        vorherigeIteration = Q;
        counter++;
    }
    for(int i = 0; i < R.zeilenzahl(); i++){
        eigenwerte.append(R.get_wert(i,i));
    }
    */
    return eigenwerte;
}
double skalarprodukt(matrizen x, matrizen y){
    //berechnet das Skalarprodukt zweier Vektoren
    double sp = 0;
    if(x.spaltenzahl() == 1){//wenn x ein Spaltenvektor ist
        x.transponieren();//dann wird er zum Zeilenvektor gemacht
    }
    if(y.zeilenzahl() == 1){//wenn y ein Zeilenvektor ist
        y.transponieren();//dann wird er zum Spaltenvektor gemacht
    }
    if(x.spaltenzahl() != y.zeilenzahl()){
        debug("Skalarprodukt geht nicht. verschiendene Dimensionen");
        return sp;
    }
    matrizen erg = x * y;//das normale Matrixprodukt wird gebildet. Da kommt eine 1x1 Matrix raus
    sp = erg.get_wert(0,0);
    return sp;
}
matrizen matrizen::kronecker(matrizen x) const {
    //bidlet das Kronecker Produkt
    matrizen erg(this->zeilenzahl()*x.zeilenzahl(), this->spaltenzahl()*x.spaltenzahl());
    for(int zeileA = 0; zeileA < this->zeilenzahl(); zeileA++){
        for(int spalteA = 0; spalteA < this->spaltenzahl(); spalteA++){
            for(int zeileB = 0; zeileB < x.zeilenzahl(); zeileB++){
                for(int spalteB = 0; spalteB < x.spaltenzahl(); spalteB++){

                    int spalte = spalteA * x.spaltenzahl() + spalteB;
                    int zeile = zeileA *  x.zeilenzahl() + zeileB;
                    double wert = this->get_wert(zeileA, spalteA) * x.get_wert(zeileB, spalteB);
                    erg.set_wert(wert, zeile, spalte);
                }
            }
        }
    }
    return erg;
}
int matrizen::kleinsteDimension() const {
    //gibt die kleinere Dimension zurück. Wenn beide gleich groß sind dann irgendeine
    if(this->zeilenzahl() < this->spaltenzahl()){
        return this->zeilenzahl();
    }else{
        return this->spaltenzahl();
    }
}
double matrizen::betrag() const {
    //berechnet den Betrag eines Vektors
    /*
    double betrag = 0;
    matrizen kopie(this);
    if(kopie.zeilenzahl() == 1){
        kopie.transponieren();
    }
    if(kopie.spaltenzahl() != 1){
        debug("Betrag einer Matrix kann nicht gebildet werden");
        return 0;
    }
    for(int i = 0; i < kopie.zeilenzahl(); i++){
        betrag += kopie.get_wert(i,0) * kopie.get_wert(i,0);
    }
    */
    double betrag = this->betragsquadrat();
    betrag = pow(betrag, 0.5);
    return betrag;
}
double matrizen::betragsquadrat() const {
    //berechnet den Betrag im Quadrat eines Vektors
    double betrag = 0;
    matrizen kopie(this);
    if(kopie.zeilenzahl() == 1){
        kopie.transponieren();
    }
    if(kopie.spaltenzahl() != 1){
        debug("Betrag einer Matrix kann nicht gebildet werden");
        return 0;
    }
    for(int i = 0; i < kopie.zeilenzahl(); i++){
        betrag += kopie.get_wert(i,0) * kopie.get_wert(i,0);
    }
    return betrag;
}
QVector<double> matrizen::charakteristischesPolynom() const {
    //Algorithmus von Samuelson-Berkowitz
    //https://de.wikipedia.org/wiki/Algorithmus_von_Samuelson-Berkowitz
    if(!this->isSquare()){
        debug("Charakterischrisches polynom nur für quadratische Matrizen");
        return QVector<double>();
    }
    matrizen vect(2,1);
    vect.set_wert(1,0,0);
    vect.set_wert(-this->get_wert(0,0), 1, 0);

    for(int r = 1; r < this->zeilenzahl(); r++){
        auto q= this->q(r+1);
        q.Toeplitz();
        vect = q * vect;
    }
    QVector<double> polynom;
    for(int i = 0; i < vect.zeilenzahl(); i++){
        polynom.append(vect.get_wert(i,0));
    }
    return polynom;
}
void matrizen::Toeplitz(){
    if(this->spaltenzahl() != 1){
        debug("Toeplitzmatrix kann nicht gebildet werden");
    }
    int d = this->zeilenzahl() - 1;
    matrizen kopie(this);
    this->resize(d + 1, d);
    for(int zeilenindex = 0; zeilenindex < d + 1; zeilenindex++){
        for(int spaltenindex = 0; spaltenindex < d; spaltenindex++){
            if(zeilenindex >= spaltenindex){
                int k = zeilenindex - spaltenindex;
                auto wert = kopie.get_wert(k, 0);
                this->set_wert(wert, zeilenindex, spaltenindex);
            }else{
                this->set_wert(0, zeilenindex, spaltenindex);
            }
        }
    }
}
matrizen matrizen::R(int zeilenindex) const {
    auto zeile = this->get_zeile(zeilenindex);
    while(zeile.spaltenzahl() > zeilenindex){
        zeile.spalteLoeschen(zeilenindex);
    }
    return zeile;
}
matrizen matrizen::S(int spaltenindex) const {
    auto spalte = this->get_spalte(spaltenindex);
    while(spalte.zeilenzahl() > spaltenindex){
        spalte.zeileLoeschen(spaltenindex);
    }
    return spalte;
}
matrizen matrizen::A(int n) const {
    matrizen kopie(this);
    kopie.resize(n, n);
    return kopie;
}
matrizen matrizen::power(int n) const {
    matrizen kopie(this);
    if(n == 0){
        kopie.toIdentity();
        return kopie;
    }
    for(int i = 1; i < n; i++){
        kopie = kopie * kopie;
    }
    return kopie;
}
matrizen matrizen::q(int n) const {
    int r = n - 1;
    matrizen erg(n + 1, 1);
    erg.set_wert(1,0,0);
    erg.set_wert(-get_wert(r,r),1,0);
    for(int k = 1; k <= r; k++){
        auto R = this->R(r);
        auto A = this->A(r);
        A = A.power(k-1);
        auto S =  this->S(r);
        auto wert = R * A * S;
        erg.set_wert(-wert.get_wert(0,0), k+1, 0);
    }
    return erg;
}
matrizen matrizen::unterbestimmt()const{
    matrizen kopie(this);
    kopie.gauss();
    kopie.nullZeilenLoeschen();
    int freiheitsgrade = kopie.spaltenzahl() - kopie.zeilenzahl() - 1;
    if(freiheitsgrade != 1){
        debug("untrbestimmt. nicht implementiert");
        return matrizen();
    }
    matrizen erg(this->zeilenzahl(), freiheitsgrade);
    erg.set_wert(1, this->zeilenzahl()-1, 0);
    for(int diagIndex = kopie.kleinsteDimension()-1; diagIndex >= 0; diagIndex--){
        double wert = kopie.get_wert(diagIndex, kopie.spaltenzahl()-1);
        for(int j = diagIndex + 1;j < kopie.spaltenzahl()-1;j++ ){
            wert -= kopie.get_wert(diagIndex, j) * erg.get_wert(j,0);
        }
        erg.set_wert(wert, diagIndex, 0);
    }
    return erg;
}
