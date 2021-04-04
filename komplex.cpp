#include "komplex.h"

komplex::komplex()
{
    //Standartonstrukter der Real & Imaginärteil auf 0 setzt
    this->set_real(0);
    this->set_imag(0);
}
komplex::komplex(double real, double imag){
    //Konstruktor der zwei Argumente nimmt und diese zuweist
    this->set_real(real);
    this->set_imag(imag);
}
komplex::komplex(double d){
    //Konstruktor der ein Argument nimmt und den Realteil auf den Input setzt und den Imaginärteil auf 0
    this->set_real(d);
    this->set_imag(0);
}
double komplex::get_real() const {
    //gibt den Realteil zurück
    return this->real;
}
double komplex::get_imag() const {
    //gibt den Imaginätteil zurück
    return this->imag;
}
void komplex::set_real(double real){
    //setzt den Realteil
    this->real = real;
}
void komplex::set_imag(double imag){
    //setzt den Imaginärteil
    this->imag = imag;
}
double komplex::betrag() const {
    //gibt den Betrag der komplexen Zahl zurück
    return std::pow(this->get_real()*this->get_real()+this->get_imag()*this->get_imag(), 0.5);
}
double komplex::winkel() const {
    //gibt den Winkel zur positiven x-Achse zurück
    if(istUngefaehrGleich(this->get_real(), 0) && istUngefaehrGleich(this->get_imag(), 0))
    {
        //hier fliegt uns was mächtig um die Ohren
        debug("Winkelbetimmung mit zwei Inputs die Null sind geht nicht");
        return 0;
    }else
    {
        return std::atan2(this->get_imag(), this->get_real());
    }
}
komplex komplex::toKaart() const {
    //gibt die komplexe Zahl in kaartesischer Form zurück
    //sollte eig nicht außerhalb dieser Klasse benutzt werden
    double real = this->get_real() * cos(this->get_imag());
    double imag = this->get_real() * sin(this->get_imag());
    return komplex(real, imag);
}
komplex komplex::toPol() const {
    //gibt eine komplexe Zahl zurück deren Realteil der betrag und deren Imaginärteil der Winkel ist
    //sollte eig nicht außerhalb dieser Klasse benutzt werden
    return komplex(this->betrag(), this->winkel());
}

komplex komplex::operator+(komplex z) const {
    //addiert zwei komplexe Zahlen
    return komplex(this->get_real()+z.get_real(), this->get_imag()+z.get_imag());
}
komplex komplex::operator-(komplex z) const {
    //subtrahiert zwei komplexe Zahlen
    return komplex(this->get_real()-z.get_real(), this->get_imag()-z.get_imag());
}
komplex komplex::operator*(komplex z) const {
    //multipliziert zwei komplexe Zahlen
    return komplex((this->get_real()*z.get_real())-(this->get_imag()*z.get_imag()),
                   (this->get_real()*z.get_imag())+(this->get_imag()*z.get_real()));
}
komplex komplex::operator/(komplex z) const {
    //dividiert zwei komplexe Zahlen
    if(istUngefaehrGleich(z.get_imag(), 0) && istUngefaehrGleich(z.get_real(), 0)){
        debug("Teilen durch 0+0j geht nicht!!!");
        return komplex();
    }else if(istUngefaehrGleich(this->betrag(), 0)){
        return komplex();
    }else if(istUngefaehrGleich(z.get_imag(), 0)){
        return komplex(this->get_real() / z.get_real(), this->get_imag() / z.get_imag());
    }else{
        return (komplex(this->betrag()/z.betrag(), this->winkel()-z.winkel())).toKaart();
    }

}


komplex komplex::operator+=(komplex z) const {
    return (*this + z);
}
komplex komplex::operator-=(komplex z) const {
    return (*this - z);
}
komplex komplex::operator*=(komplex z) const {
    return (*this * z);
}
komplex komplex::operator/=(komplex z) const {
    return (*this / z);
}


bool komplex::operator==(komplex a) const {
    //vergleicht ob zwei komplexe Zahlen gleich sind
    if(istUngefaehrGleich(this->get_real(), a.get_real()) && istUngefaehrGleich(this->get_imag(), a.get_imag())){
        return true;
    }else{
        return false;
    }
}
bool komplex::operator!=(komplex a) const {
    //vergleicht ob zwei komplexe Zahlen ungleich sind
    return (!(*this == a));
}
QString komplex::toQstring(void) const {
    //wandelt eine komplexe Zahl in einen String um
    QString s = "";
    komplex kopie;
    kopie.set_imag(this->get_imag());
    kopie.set_real(this->get_real());
    kopie.runden();
    if(istUngefaehrGleich(kopie.get_imag(), 0)){
        s += QString::number(kopie.get_real());
    }else if(istUngefaehrGleich(kopie.get_real(), 0)){
        s += QString::number(kopie.get_imag());
        s += "j";
    }else{
        s += QString::number(kopie.get_real());
        if(kopie.get_imag()>=0){
            s+= " + ";
        }else{
            s+= " - ";
        }
        s += QString::number(abs(kopie.get_imag()));
        s += "j";
    }
    return s;
}
komplex pow(komplex z, double d){
    //potentziert eine komplexe Zahl mit einer reellen Zahl
    if(istUngefaehrGleich(d, 0)){
        return komplex(1);
    }else if(istUngefaehrGleich(d, 1)){
        return z;
    }else{
        komplex x = (komplex(pow(z.betrag(), d), d * z.winkel())).toKaart();
        if(x.get_real() != x.get_real()){
            debug("NAN 3");
        }
        return x;
    }
}
komplex pow(double d, komplex z){
    //potenziert eine reelle Zahl mit einer komplexen Zahl
    if(istUngefaehrGleich(z.get_imag(), 0)){
        return komplex(pow(d, z.get_real()));
    }else{
        komplex x = ((komplex(pow(d, z.get_real()), z.get_imag()*log(d))).toKaart());
        if(x.get_real() != x.get_real()){
            debug("NAN 2");
        }
        return x;
    }
}
komplex pow(komplex a, komplex b){
    //potenziert zwei komplexe Zahlen
    if(istUngefaehrGleich(a.get_imag(), 0)){
        return pow(a.get_real(), b);
    }else if(istUngefaehrGleich(b.get_imag(), 0)){
        return pow(a, b.get_real());
    }else{
        komplex x = (pow(a.betrag(), b)*pow(M_E, (komplex(-b.get_imag(), b.get_real())*a.winkel())));
        if(x.get_real() != x.get_real()){
            debug("NAN 1");
        }
        return x;
    }
}
void debug(komplex z){
    //gibt eine komplexe Zahl in der Konsole aus
    QString s = z.toQstring();
    debug(s);
    return;
}
void komplex::runden(int nachkommastellen){
    //rundet eine komplexe Zahl auf eine gewisse Anzahl nachkommastellen
    double nks = nachkommastellen;
    double real = this->get_real();
    double imag = this->get_imag();
    real *= pow(10, nks);
    imag *= pow(10, nks);
    real = round(real);
    imag = round(imag);
    real *= pow(10, -nks);
    imag *= pow(10, -nks);
    this->set_real(real);
    this->set_imag(imag);
}

bool istUngefaehrGleich(komplex zahl1, komplex zahl2, double genauigkeit){
    if(!istUngefaehrGleich(zahl1.get_real(), zahl2.get_real(), genauigkeit)){
        return false;
    }
    if(!istUngefaehrGleich(zahl1.get_imag(), zahl2.get_imag(), genauigkeit)){
        return false;
    }
    return true;
}
