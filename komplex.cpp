#include "komplex.h"

komplex::komplex()
{

}
komplex::komplex(double real, double imag){
    this->set_real(real);
    this->set_imag(imag);
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
    return std::pow(this->get_real()*this->get_real()*this->get_imag()*this->get_imag(), 0.5);
}
double komplex::winkel() const {
    if(this->get_real() == 0 && this->get_imag() == 0)
    {
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
komplex komplex::operator^(double d){
    return komplex(this->betrag()^d, d*this->winkel()).toKaart();
}
komplex komplex::operator+(komplex z){
    return komplex(this->get_real()+z.get_real(), this->get_imag()+z.get_imag());
}
komplex komplex::operator-(komplex z){
    return komplex(this->get_real()-z.get_real(), this->get_imag()-z.get_imag());
}
komplex komplex::operator*(komplex z){
   return (komplex(this->betrag()*z.betrag(), this->winkel()+z.winkel())).toKaart();
}
komplex komplex::operator/(komplex z){
   return (komplex(this->betrag()/z.betrag(), this->winkel()-z.winkel())).toKaart();
}

