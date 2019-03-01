#include "Figura.h"

#include <sstream>

using namespace lab4;

Figura::Figura(const Punkt & _srodek, const string & _etykieta)
        : srodek(_srodek)
        , etykieta(_etykieta)
{
    //ctor
}


void Figura::przesun(const Punkt & sr)
{
    srodek.setX(sr.getX());
    srodek.setY(sr.getY());
}

string Figura::opis()const // srodek maja wspolny
{
    std::ostringstream os;
    srodek.zapisz(os);
    return os.str();
}

bool Figura::zapisz(ostream & os)const
{
    os << endl << endl << etykieta << ": ";
    srodek.zapisz(os);
    return os;
}

bool Figura::wczytaj(istream & is)
{
    srodek.wczytaj(is);
    is >> etykieta;
    return is;
}
