#include <iostream>
#include "Poligon.h"
#include "Piksel.h"
using namespace std;

int main()
{
    try{
    Piksel p1(480, 481);
    Piksel p2(240, 241);
    Piksel p3(3, 3);
    Piksel p4(4, 4);
    cout << "p1.x = " << p1.getX() << endl;
    cout << "p1.y = " << p1.getY() << endl;
    cout << "p2.x = " << p2.getX() << endl;
    cout << "p2.y = " << p2.getY() << endl;
    cout << "p3.x = " << p3.getX() << endl;
    cout << "p3.y = " << p3.getY() << endl;
    cout << "p4.x = " << p4.getX() << endl;
    cout << "p4.y = " << p4.getY() << endl;

    p3 = p4;
    cout << "p3 = p4" << endl;
    cout << "p3.x = " << p3.getX() << endl;
    cout << "p3.y = " << p3.getY() << endl;

    // konstruktor kopiujacy
    Piksel p5(p4);
    cout << "Piksel p5(p4);" << endl;
    cout << "p5.x = " << p5.getX() << endl;

    Poligon pol(3);
    cout << "pol.size = " << pol.getSize() << endl;
    pol.addPiksel(p1);
    pol.addPiksel(p2);
    pol.addPiksel(p3);

    // konstruktor przenoszacy
    Poligon pol2(move(pol));
    cout << "pol2.getSize() = " << pol2.getSize() << endl;
    cout << "pol.getSize() = " << pol.getSize() << endl;

    // konstruktor kopiujacy
    Poligon pol3(pol2);
    cout << "pol3.getSize() = " << pol3.getSize() << endl;
    cout << "pol2.getSize() = " << pol2.getSize() << endl;
    pol.addPiksel(p4);
}
    catch(string ex){
        cout << ex << endl;
    }
    return 0;
}
