#include "Punkt.h"

using namespace lab4;

bool Punkt::zapisz(ostream & os)const
{
    os << "\nSrodek = (" << x << ", " << y << ")";
    return os;
}

bool Punkt::wczytaj(istream & is)
{
    is >> x >> y;
    return is;
}

ostream& operator<< (ostream &out, Punkt const& p)
{
    out << "(" << p.getX() << ", " << p.getY() << ")";
    return out;
}
