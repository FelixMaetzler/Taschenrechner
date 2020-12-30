#include "komplex.h"

komplex::komplex()
{
    this->set_real(0);
    this->set_imag(0);
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
    if(z.get_imag() == 0.0 && z.get_real() == 0.0){
        debug("Teilen durch 0+0j geht nicht!!!");
        return komplex();
    }else if(this->betrag() == 0){
        return komplex();
    }else if(this->get_imag() == 0.0 && z.get_imag() == 0.0){
        return komplex((this->get_real()/z.get_real()));
    }else{
        return (komplex(this->betrag()/z.betrag(), this->winkel()-z.winkel())).toKaart();
    }

}

bool komplex::operator==(komplex a){
    if(this->get_real() == a.get_real() && this->get_imag()==a.get_imag()){
        return true;
    }else{
        return false;
    }
}
bool komplex::operator!=(komplex a){
    return (!(*this == a));
}


QString komplex::toQstring(void)const{
    QString s = "";
    if(this->get_imag() == 0.0){
        s += QString::number(this->get_real());
    }else if(this->get_real() == 0.0){
        s += QString::number(this->get_imag());
        s += "j";
    }else{
        s += QString::number(this->get_real());
        if(this->get_imag()>=0){
            s+= " + ";
        }else{
            s+= " - ";
        }
        s += QString::number(abs(this->get_imag()));
        s += "j";
    }

    return s;
}



komplex pow(komplex z, double d){
    if(d == 0.0){
        return komplex(1.0);
    }else if(d == 1.0){
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
    if(z.get_imag() == 0.0){
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
    if(a.get_imag() == 0.0){
        return pow(a.get_real(), b);
    }else if(b.get_imag() == 0.0){
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
    QString s = z.toQstring();
    debug(s);
    return;
}

