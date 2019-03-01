#include "Poligon.h"
#include <iostream>
using namespace std;

// destructor
Poligon :: ~Poligon()
{
    delete[] arr;
}

// Copy constructor/konstruktor kopiujacy
Poligon :: Poligon(const Poligon & other) : arr(new Piksel[other.size]), size(other.size), top(other.top)
{
    copy(other.arr, other.arr + top, arr);
}

// operator podstawienia
Poligon& Poligon :: operator=(const Poligon & other)
{
    if(this != &other)
    {
        delete[] arr;

        size = other.size;
        arr = new Piksel[size];
        top = other.top;
        copy(other.arr, other.arr+size, arr);
    }
    return *this;
}

Poligon& Poligon :: operator=(Poligon&& other)
{
    arr = other.arr;
    size = other.size;
    top = other.top;
    other.arr = new Piksel[0];
    other.top = other.size = 0;
    return *this;
}

// konstruktor przenoszacy
Poligon :: Poligon(Poligon && other) : arr(new Piksel[0]), size(other.size), top(other.top)
{
    if(this != &other)
    {
        auto tmp = other.arr;
        other.arr = arr;
        arr = tmp;
        other.top = 0;
        other.size = 0;
    }
}

Piksel Poligon :: getPiksel(const int i) const
{
    if(i < 0 || i >= top) throw string("Wrong index.");
    return arr[i];
}

void Poligon :: addPiksel(Piksel p)
{
    if(top == size) throw string("Array is full.");
    arr[top++] = Piksel(p);
}
