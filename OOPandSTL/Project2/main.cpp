#include <iostream>
#include "obiekty.h"

using namespace std;

int main()
{
    // odejmowanie wektorow
    cout << "Odejmowanie wektorow:\n";
    Vector v1(1, 2);
    Vector v2(3, 4);
    cout << v1 << " - " << v2 << " = " << v1 - v2 << "\n\n";

    // mnozenie macierzy przez liczbe
    cout << "Mnozenie macierzy przez liczbe:\n";
    Matrix m(1, 2, 3, 4);
    cout << m << " * 3 =\n";
    cout << m * 3 << "\n\n";

    // mnozenie wektora przez macierz
    cout << "\nMnozenie wektora przez macierz:\n";
    cout << v1 <<"*\n"<<m<<"=\n"<<v1 * m << "\n\n";

    // inkrementacja wektora
    cout << "\nInkrementacja wektora:\n";
    cout << v1 << endl;
    cout << ++v1 << endl;
    cout << v1 << endl;
    cout << "\n\n";
    cout << v1 << endl;
    cout << v1++ << endl;
    cout << v1 << "\n\n";

    // zmiana znaku macierzy
    cout << "\nZmiana znaku macierzy:\n";
    cout << -m << endl;

    // porównywanie dwóch wektorów
    cout << "\nPorownywanie dwoch wektorow:\n";
    cout << v1 << endl;
    cout << v2 << endl;
    cout << (v1 == v2) << endl;
    cout << (v1 == v1) << endl;

    // operator tablicowy
    cout << "\nOperator tablicowy:\n";
    cout << v1[0] << " " << v1[1] << endl;

    // operator konwersji
    cout << "\nOperator konwersji:\n";
    Matrix mDet(5, 3, 2, 1);
    cout << (float)m << "\n\n";
    cout << (float)mDet << endl;
}
