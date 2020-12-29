#include "komplex.h"

komplex::komplex()
{

}
komplex::komplex(double real, double imag){
    this->set_real(real);
    this->set_imag(imag);
}
komplex::komplex(double d){
    this->set_real(d);
    this->set_imag(0);
}
double komplex::get_real() const {
    return this->real;
}

double komplex::get_imag() const {
    return this->imag;
}
void komplex::set_real(double real){
    this->real = real;
}
void komplex::set_imag(double imag){
    this->imag = imag;
}
double komplex::betrag() const {
    return std::pow(this->get_real()*this->get_real()+this->get_imag()*this->get_imag(), 0.5);
}
double komplex::winkel() const {
    if(this->get_real() == 0 && this->get_imag() == 0)
    {
        //hier fliegt uns was mächtig um die Ohren
        debug("Winkelbetimmung mit zwei Inputs die Null sind geht nicht");
        return 0;
    }else
    {
    return std::atan2(this->get_imag(), this->get_real());
    }
}
komplex komplex::toKaart(){
    double real = this->get_real() * cos(this->get_imag());
    double imag = this->get_real() * sin(this->get_imag());
    return komplex(real, imag);
}
komplex komplex::toPol(){
    return komplex(this->betrag(), this->winkel());
}
komplex komplex::operator*(double d){
    return komplex(this->get_real()*d, this->get_imag()*d);
}
komplex komplex::operator/(double d){
    return komplex(this->get_real()/d, this->get_imag()/d);
}
komplex komplex::operator+(komplex z){
    return komplex(this->get_real()+z.get_real(), this->get_imag()+z.get_imag());
}
komplex komplex::operator-(komplex z){
    return komplex(this->get_real()-z.get_real(), this->get_imag()-z.get_imag());
}
komplex komplex::operator*(komplex z){
   return komplex((this->get_real()*z.get_real())-(this->get_imag()*z.get_imag()),
                  (this->get_real()*z.get_imag())+(this->get_imag()*z.get_real()));
}
komplex komplex::operator/(komplex z){
   return (komplex(this->betrag()/z.betrag(), this->winkel()-z.winkel())).toKaart();
}



komplex pow(komplex z, double d){
    return (komplex(pow(z.betrag(), d), d * z.winkel())).toKaart();
}
komplex pow(double d, komplex z){
    return ((komplex(pow(d, z.get_real()), z.get_imag()*log(d))).toKaart());
}
komplex pow(komplex a, komplex b){
    return (pow(a.betrag(), b)*pow(M_E, (komplex(-b.get_imag(), b.get_real())*a.winkel())));
}
void debug(komplex z){
    QString s = "";
    s += QString::number(z.get_real());
    if(z.get_imag()>=0){
        s+= " + ";
    }else{
        s+= " - ";
    }
    s += QString::number(abs(z.get_imag()));
    s += "";
    s += "j";
    debug(s);
    return;
}

