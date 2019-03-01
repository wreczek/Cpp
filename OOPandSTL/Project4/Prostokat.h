#ifndef PROSTOKAT_H
#define PROSTOKAT_H

#include "Figura.h"

namespace lab4
{
    class Prostokat : public Figura
    {
        public:
            Prostokat(const Punkt & sr, const string & _etykieta, const double _a, const double _b) : Figura(sr, _etykieta), a(_a), b(_b) {}
            double pole()const { return a*b; }
            string opis()const; // kwadrat tak samo
            virtual bool zapisz(ostream & os)const;
            virtual bool wczytaj(istream & is);
        protected:
            double a;
            double b;
    };
}
#endif // PROSTOKAT_H
