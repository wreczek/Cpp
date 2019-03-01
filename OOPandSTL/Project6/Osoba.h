#ifndef OSOBA_H
#define OSOBA_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Osoba
{
private:
    string imie, nazwisko;
    int rokUr;
public:
    Osoba();
    virtual ~Osoba() {}
    int getRokUr()const { return rokUr; }
    string getImie() { return imie; }
    string getNazwisko() { return nazwisko; }
    string getKlucz()const;
    void display()const;
    bool operator<(const Osoba& other)const;
};

#endif // OSOBA_H
