#include "Prostokat.h"

#include <sstream>

using namespace lab4;

string Prostokat::opis()const // kwadrat tak samo
{
    ostringstream os;
    Figura::zapisz(os);
    os << ", boki to " << a << " i " << b << ", pole: " << pole();
    return os.str();
}

bool Prostokat::zapisz(ostream & os)const
{
    bool c = Figura::zapisz(os);
    os << " a: " << a << ", b: " << b << ", pole: " << pole();
    return (c && os);
}

bool Prostokat::wczytaj(istream & is)
{
    bool c = Figura::wczytaj(is);
    is>>a>>b;
    return (is && c);
}
