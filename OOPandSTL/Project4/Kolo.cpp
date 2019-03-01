#include "Kolo.h"

#include <sstream>

using namespace lab4;

string Kolo::opis()const
{
    ostringstream os;
    Figura::zapisz(os);
    os << ", promien: " << promien << ", pole: " << pole();
    return os.str();
}

bool Kolo::zapisz(ostream & os)const
{
    bool a = Figura::zapisz(os);
    os << " promien: " << promien << ", pole: " << pole();
    return os && a;
}

bool Kolo::wczytaj(istream & is)
{
    bool a = Figura::wczytaj(is);
    is >> promien;
    return is && a;
}
