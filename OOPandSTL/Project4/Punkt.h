#ifndef PUNKT_H
#define PUNKT_H

#include <istream>
#include <ostream>

using namespace std;

namespace lab4
{
    class Punkt
    {
        public:
            Punkt(double _x, double _y) : x(_x), y(_y) {}
            void setX(const double _x) { x = _x; }
            void setY(const double _y) { y = _y; }
            double getX()const { return x; }
            double getY()const { return y; }
            bool zapisz(ostream & os)const;
            bool wczytaj(istream & is);
            friend ostream& operator<< (ostream &out, Punkt const& p); // ?
        private:
            double x;
            double y;
    };
}
#endif // PUNKT_H
