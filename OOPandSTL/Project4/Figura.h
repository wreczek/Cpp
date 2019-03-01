#ifndef FIGURA_H
#define FIGURA_H

#include "Punkt.h"
namespace lab4
{
    class Figura
    {
        public:
            Figura(const Punkt & _srodek, const string & _etykieta);
            virtual ~Figura() {}
            void przesun(const Punkt & sr);
            virtual string opis()const; // srodek maja wspolny
            virtual double pole()const = 0; // pole kazdy inaczej
            virtual bool zapisz(ostream & os)const;
            virtual bool wczytaj(istream & is);
        protected:
            Punkt srodek;
            string etykieta;
    };
}
#endif // FIGURA_H
