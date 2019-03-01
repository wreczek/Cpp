#include <iostream>
#include "Punkt.h"
#include "Figura.h"
#include "Kolo.h"
#include "Prostokat.h"
#include "Kwadrat.h"

using namespace std;
using namespace lab4;

int main()
{
    cout << "Tworzenie punktow.\n";
    Punkt p1(1, 2);
    Punkt * p2 = new Punkt(2, 4);
    Punkt p3(3, 4);
    Punkt p4(4, -1);
    Punkt p5(5, 5);
    p1.zapisz(cout);
    (*p2).zapisz(cout);

    cout << "\nTworzenie figur.\n";
    Figura * f1 = new Kolo(p1, "Kolo1", 1);
    Figura * f2 = new Kolo((*p2), "Koleczko", 2);
    Prostokat f3(p3, "Prostokacik", 3, 5);
    Figura * f4 = new Kwadrat(p4, "Kwadracik", 4);
    Figura * f5 = new Kwadrat(p5, "Kwadrat1", 8);
    Figura * figury[5] = {f1, f2, &f3, f4, f5};

    cout << "\n---Opisywanie: ---\n";
    cout << (*f1).opis() << endl;
    cout << (*f2).opis() << endl;
    cout << f3.opis() << endl;
    cout << (*f4).opis() << endl;
    cout << (*f5).opis() << endl;

    cout << "\n---Zapisywanie: ---";
    (*f1).zapisz(cout);
    (*f2).zapisz(cout);
    f3.zapisz(cout);
    (*f4).zapisz(cout);
    (*f5).zapisz(cout);

    cout << "\n\n---Wczytywanie: ---\n\n";
    Figura * f6 = new Kolo(p1, "proba", 10);
    cout << (*f6).opis() << endl;
    cout << (*f6).wczytaj(cin) << endl;
    cout << (*f6).opis() << endl << endl;

    Figura * f7 = new Prostokat(p1, "proba2", 10, 15);
    cout << (*f7).opis() << endl;
    cout << (*f7).wczytaj(cin) << endl;
    cout << (*f7).opis() << endl << endl;

    Figura * f8 = new Kwadrat(p1, "proba3", 20);
    cout << (*f8).opis() << endl;
    (*f8).wczytaj(cin);
    cout << (*f8).opis() << endl << endl;
    (*f8).zapisz(cout);

    // cout << "Punkt to " << p1; // ?
}
