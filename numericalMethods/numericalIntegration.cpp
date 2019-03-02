#include <iostream>
#include <cmath>

#define e 3.1415926535979323846

using namespace std;

double rectangularIntegration(double a, double b, int n, double (*f)(double));
double trapezoidIntegration(double a, double b, int n, double (*f)(double));
double SimpsonsRule(double a, double b, int n, double (*f)(double));

int main()
{
    cout << endl << endl;
    double a, b;
    cout << "Poczatek przedzialu: ";    cin >> a;
    cout << "Koniec przedzialu: ";      cin >> b;

    int n;
    cout << "Liczba krokow: ";          cin >> n;
    cout << "\nWzor prostokatow:\nP = " << rectangularIntegration(a, b, n, [](auto x) { return 4*sin(x); });
    cout << "\n\nWzor trapezow:\nP = " << trapezoidIntegration(a, b, n, [](auto x) { return 4*sin(x); });
    cout << "\n\nWzor Simpsona:\nP = " << SimpsonsRule(a, b, n, [](auto x) { return 4*sin(x); });
    cout << endl << endl;
    return 0;
}

double rectangularIntegration(double a, double b, int n, double (*f) (double))
{

    double sum = 0;
    double interval = (b-a)/n;
    for(int i = 0 ; i < n; i++)
    {
        double number = a + (double)i * interval;
        sum += interval * f((number + number + interval)/2);
    }
    return sum;
}

double trapezoidIntegration(double a, double b, int n, double (*f) (double))
{
    double sum = 0;
    double interval = (b-a)/n;
    for(int i = 0 ; i < n; i++)
    {
        double number = a + (double)i * interval;
        sum += interval * (f(number) + f(number + interval))/2;
    }
    return sum;
}

double SimpsonsRule(double a, double b, int n, double (*f) (double))
{
    // Z: n musi byc parzyste, n >= 4
    double sum = 0;
    double interval = (b-a)/n;
    for(int i = 0 ; i < n; i += 2)
    {
        double number = a + (double)i * interval;
        sum += interval * (f(number) + 4 * f(number + interval) + f(number + 2 * interval))/3 ;
    }
    return sum;
}
