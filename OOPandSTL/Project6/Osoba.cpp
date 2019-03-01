#include "Osoba.h"

//const int maxSize = 5;
#define maxSize 5
string imiona[maxSize] = {"Wiktor", "Krystian", "Mateusz", "Marian", "Szymon"};
string nazwiska[maxSize] = {"Nowak", "Kowalski", "Michalski", "Gajecki", "Majewski"};

Osoba::Osoba()
{
    imie = imiona[(rand() % 5)];
    nazwisko = nazwiska[(rand() % 5)];
    rokUr = 1950 + (rand() % 61);
}

string Osoba::getKlucz()const
{
    return nazwisko + imie;
}

void Osoba::display()const
{
    cout << imie << " " << nazwisko << " " << rokUr << endl;
}

bool Osoba::operator<(const Osoba& other)const
{
    if(other.getKlucz() == getKlucz())
    {
        other.display();
        display();
        cout << "Dwie takie same osoby!\n";
    }
    return other.getKlucz() == getKlucz();
}
