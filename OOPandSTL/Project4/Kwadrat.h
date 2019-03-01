#ifndef KWADRAT_H
#define KWADRAT_H

#include "Prostokat.h"

namespace lab4
{
    class Kwadrat : public Prostokat
    {
        public:
            Kwadrat(const Punkt & sr, const string & _etykieta, const double _a) : Prostokat(sr, _etykieta, _a, _a) {}
            virtual ~Kwadrat() {}
            //bool zapisz(ostream & os)const;
            //bool wczytaj(istream & is);
    };
}
#endif // KWADRAT_H


