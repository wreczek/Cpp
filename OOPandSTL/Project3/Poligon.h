#ifndef POLIGON_H_INCLUDED
#define POLIGON_H_INCLUDED
#include "Piksel.h"
class Poligon
{
private:
    Piksel * arr;
    int size;
    int top;
public:
    // konstruktory
    Poligon() : arr(new Piksel[10]), size(10), top(0) {}
    Poligon(int n) : arr(new Piksel[n]), size(n), top(0) {}

    // destruktor
    virtual ~Poligon();

    // Copy constructor/konstruktor kopiujacy
    Poligon(const Poligon & other);

    // Copy assignment operator/operator przypisania
    Poligon& operator=(const Poligon & other);

    // przenoszacy operator podstawienia
    Poligon& operator=(Poligon&& other);

    // Move constructor.
    Poligon(Poligon && other); // nie dziala

    // gettery
    Piksel getPiksel(int n) const;
    int getSize(){ return size; }
    int getTop(){ return top; }

    // dodawanie piksela
    void addPiksel(Piksel p);
};

#endif // POLIGON_H_INCLUDED
