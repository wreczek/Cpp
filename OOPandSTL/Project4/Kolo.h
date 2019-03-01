#ifndef KOLO_H
#define KOLO_H

#include "Figura.h"

namespace lab4
{
    class Kolo : public Figura
    {
        public:
            Kolo(const Punkt & _srodek, const string & _etykieta, const double _promien) : Figura(_srodek, _etykieta), promien(_promien) {}
            double pole()const { return 3.1416*promien*promien; }
            string opis()const; // srodek wspolny
            bool zapisz(ostream & os)const;
            bool wczytaj(istream & is);
        protected:
            double promien;
    };
}
#endif // KOLO_H
