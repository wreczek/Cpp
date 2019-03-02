#include <iostream>
#include <cmath>

using namespace std;

void interpolation(double (*f) (double), double n);

int main()
{
    cout << "Liczba wezlow interpolacji: ";
    double n;
    cin >> n;
    interpolation([](auto x){ return sqrt(x); }, n);
    interpolation([](auto x){ return sin(x); }, n);
    interpolation([](auto x){ return x*x*x+2*x; }, n);
}

void interpolation(double (*f) (double), double n)
{
    double x = 0;
    double args[(int)n];
    double values[(int)n];
    double interval = 10;
    double jump = interval/(n-1);   // punkty miedzy wezlami
    cout << "\n\nWezly interpolacji:\n";
    for(double i = 0; i < n; i++)
    {
        x = i * interval/(n-1); // argumenty[i]
        cout << "\tx"<< i << " = " << x;
        cout << ", f(x" << i << ") = " << f(x) << endl;
        args[(int)i] = x;
        values[(int)i] = f(x);       // wartosci[i]
    }
    double arg = jump/2;
    cout << "\nPunkty pomiedzy wezlami:\n";
    for(int i = 0; i < n-1; i++)
    {
        cout << "f("<<arg<<") = "<<f(arg)<<endl;
        arg += jump;
    }
    cout << "Wartosci wielomianu interpolujacego:";
    arg = jump/2;
    double result;
    double factor;
    for(int k = 0; k < n-1; k++)
    {
        result = 0;
        for(int i = 0; i < n; i++)
        {
            factor = 1;
            for(int j = 0; j < n; j++)
            {
                if(i == j)  continue;
                factor *= (arg - args[j])/(args[i] - args[j]);
            }
            result += values[i] * factor;
        }
        cout << "\nPrzyblizenie wartosci funkcji f("<<arg<<") = "<<result;
        arg += jump;
    }
}
