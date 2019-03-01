#include <iostream>
#include <iomanip>

using namespace std;

class time
{
private:
    int h, m, s;
    static int suma;
public:
    time() : h(12), m(0), s(0) { suma += 12*60*60; }
    time(int h, int m, int s);

    int hour(){ return h; }

    void addSecond() { s++; }

    bool isEqual(time T);

    void wypisz(){ cout << h << ":" << m << ":" << s << endl; }

    static int wypiszSuma() { return suma; }

    void zapisz(ostream & os) { os<<setw(2)<<setfill('0')<<h<<":"<<setw(2)<<setfill('0')<<m<<":"<<setw(2)<<setfill('0')<<s<<endl; }

    void wczytaj(istream & is);
};

int time::suma = 0;

time::time(int h1, int m1, int s1)
{
    if(h1 < 0 || h1 > 24 || m1 < 0 || m1 > 59 || s1 < 0 || s1 > 59)
    {
        h = 12;
        m = 0;
        s = 0;
        suma += 12*60*60;
    }
    else
    {
        h = h1;
        m = m1;
        s = s1;
        suma += h1*60*60 + m1*60 + s1;
    }
}

bool time::isEqual(time T)
{
    if(h == T.h && m == T.m && s == T.s)
    {
        return true;
    }
    return false;
}

void time::wczytaj(istream & is)
{
    string time;
    is >> time;
    h = 10*(time[0]-'0')+(time[1]-'0');
    m = 10*(time[3]-'0')+(time[4]-'0');
    s = 10*(time[6]-'0')+(time[7]-'0');
}

int main()
{
    // Testowanie
    time T(0, 1, 10);
    time T1(25, 0, 0);
    time T2(0, 5, 0);
    time T3(12, 0, 0);
    cout << "\nT1: /";
    T1.wypisz();
    cout << "\nT3: ";
    T3.wypisz();
    cout << "T1 == T3? " << T1.isEqual(T3) << endl;
    T1.addSecond();
    cout << "\nT1: " << endl;
    T1.wypisz();
    cout << T1.hour() << endl;
    T1.addSecond();
    cout << "T1 == T3? " << T1.isEqual(T3) << endl;
    cout << T2.wypiszSuma();
    cout << "\nT2:" << endl;
    T2.zapisz(cout);
    cout << "T1: " << endl;
    T1.zapisz(cout);
    cout << "T3: " << endl;
    T3.zapisz(cout);
    T3.wypisz();
    cout << "T1: " << endl;
    T1.wypisz();
    T1.zapisz(cout);
    time T5(5, 6, 7);
    T5.wypisz();
    T5.zapisz(cout);
    T5.wczytaj(cin);
    T5.wypisz();
    T5.zapisz(cout);
    return 0;
}
