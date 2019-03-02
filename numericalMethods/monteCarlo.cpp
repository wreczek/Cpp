#include <iostream>
#include <random>
#include <cmath>

using namespace std;

void integralApprox(double a, double b, double (*f)(double));
void approxVolOfBall(double (*f)(double, double, double));
void approxVolOfCone(double (*f)(double, double));
void approxVolOf3dShape(double (*f)(double, double, double), double (*g)(double, double));
//-------
void integralApprox2(double a, double b, double (*f)(double));
void approxVolOfBall2(double (*f)(double, double, double));
void approxVolOfCone2(double (*f)(double, double));
void approxVolOf3dShape2(double (*f)(double, double, double), double (*g)(double, double));

int main()
{
    cout << "\nPodaj liczbe pomiarow: ";
    int n;
    cin >> n;

    for(int i = 0; i < n; ++i)
    {
        //integralApprox(1, 2, [](auto x) { return 1/(x*x); });
        //integralApprox(1, 6, [](auto x) { return 1/sqrt(x*x*x*x*x+8); });
        //integralApprox(1, 22, [](auto x) { return 1/sqrt(x+8); });
        //integralApprox(1, 22, [](auto x) { return x*x+2*x; });
        //integralApprox(1, 3, [](auto x) { return sqrt(x*x*x*x*x); });
        //approxVolOfBall([](auto x, auto y, auto z){ return x*x+y*y+z*z; });
        //approxVolOfCone([](auto x, auto y){ return sqrt(x*x+y*y); });
        approxVolOf3dShape([](auto x, auto y, auto z){ return x*x+y*y+z*z; },
                         [](auto x, auto y){ return x*x+y*y; });

        /// Druga czesc
        //integralApprox2(1, 2, [](auto x) { return 1/(x*x); });
        //integralApprox2(1, 6, [](auto x) { return 1/sqrt(x*x*x*x*x+8); });
        //integralApprox2(1, 22, [](auto x) { return 1/sqrt(x+8); });
        //integralApprox2(1, 22, [](auto x) { return x*x+2*x; });
        //integralApprox2(1, 3, [](auto x) { return sqrt(x*x*x*x*x); });
        //approxVolOfBall2([](auto x, auto y, auto z){ return x*x+y*y+z*z; });
        //approxVolOfCone2([](auto x, auto y){ return sqrt(x*x+y*y); });
        approxVolOf3dShape2([](auto x, auto y, auto z){ return x*x+y*y+z*z; },
                         [](auto x, auto y){ return x*x+y*y; });
    }

    return 0;
}

void integralApprox(double a, double b, double (*f)(double))
{
    mt19937 gen{random_device{}()};
    uniform_real_distribution <double> randomX{a, b};

    cout << "Podaj liczbe losowanych punktow: ";
    double pointsInRectangle;
    cin >> pointsInRectangle;

    double x, y;

    double max = 0;     // y - poziom gorny prostokata
    double min = 0;     // y - poziom dolny prostokata

    // wyznaczanie min i max
    for(int i{0}; i < pointsInRectangle; ++i)
    {
        x = randomX(gen);
        if(f(x) > max)
            max = f(x);
        if(f(x) < min)
            min = f(x);
    }

    uniform_real_distribution <double> randomY{min, max};

    double pointsOver0X;
    double pointsUnder0X;

    double pointsOver0XUnderFx;
    double pointsUnder0XOverFx;

    // Pk = P * k/n, n - wszystkie proby, k - trafione
    double area = 0;
    double upperArea;
    double lowerArea;
    for(int j = 0; j < pointsInRectangle; j++)
    {
        pointsOver0X = 0;
        pointsUnder0X = 0;
        pointsOver0XUnderFx = 0;
        pointsUnder0XOverFx = 0;

        for(int i{0}; i < pointsInRectangle; ++i)
        {
            x = randomX(gen);
            y = randomY(gen);

            if(y > 0)
            {
                ++pointsOver0X;
                if(y <= f(x))
                    ++pointsOver0XUnderFx;
            }
            else    // y < 0
            {
                ++pointsUnder0X;
                if(y >= f(x))
                    ++pointsUnder0XOverFx;
            }
        }
        upperArea = (pointsOver0X > 0) ? max*(b-a)*pointsOver0XUnderFx/pointsOver0X : 0;
        lowerArea = (pointsUnder0X > 0)? min*(b-a)*pointsUnder0XOverFx/pointsUnder0X : 0; // jest to liczba ujemna, jako ze min < 0
        area += (upperArea + lowerArea) / pointsInRectangle;
    }
    cout << "Pole liczone niezaleznie: " << area << endl;
}

void approxVolOfBall(double (*f)(double, double, double))
{
    const double cuboidVol = 1000;
    // kula o promieniu 5
    mt19937 gen{random_device{}()};
    uniform_real_distribution <double> randomX{-5., 5.};
    uniform_real_distribution <double> randomY{-5., 5.};
    uniform_real_distribution <double> randomZ{-5., 5.};
    cout << "\nPodaj liczbe losowanych punktow: ";
    double pointsInCuboid;
    cin >> pointsInCuboid;

    double pointsInBall;
    double vol = 0;

    double x, y, z;     // wspolrzedne w 3D

    for(int i = 0; i < pointsInCuboid; ++i)
    {
        pointsInBall = 0;

        for(int j = 0; j < pointsInCuboid; ++j)
        {
            x = randomX(gen);
            y = randomY(gen);
            z = randomZ(gen);
            if(f(x, y, z) <= 25)
                pointsInBall++;
        }
        vol += (cuboidVol * pointsInBall / pointsInCuboid) / pointsInCuboid;
    }
    cout << "Objetosc kuli o promieniu 5 wynosi " << vol << endl;
}

void approxVolOfCone(double (*f)(double, double))
{
    const double cuboidVol = 4000;
    // stozek o promieniu ui wysokosci 10
    mt19937 gen{random_device{}()};
    uniform_real_distribution <double> randomX{-10., 10.};
    uniform_real_distribution <double> randomY{-10., 10.};
    uniform_real_distribution <double> randomZ{0., 10.};
    cout << "\nPodaj liczbe losowanych punktow: ";
    double pointsInCuboid;
    cin >> pointsInCuboid;

    double pointsInCone;
    double vol = 0;

    double x, y, z;     // wspolrzedne w 3D

    for(int i = 0; i < pointsInCuboid; ++i)
    {
        pointsInCone = 0;

        for(int j = 0; j < pointsInCuboid; ++j)
        {
            x = randomX(gen);
            y = randomY(gen);
            z = randomZ(gen);
            if(z <= 10 - f(x, y))
                pointsInCone++;
        }
        vol += (cuboidVol * pointsInCone / pointsInCuboid) / pointsInCuboid;
    }
    cout << "Objetosc stozka o r=10, h=10 wynosi " << vol << endl;
}

void approxVolOf3dShape(double (*f)(double, double, double), double (*g)(double, double))
{
    const double cuboidVol = 8000;
    // kula(R=10) - walec(H=6, r=3)
    mt19937 gen{random_device{}()};
    uniform_real_distribution <double> randomX{-10., 10.};
    uniform_real_distribution <double> randomY{-10., 10.};
    uniform_real_distribution <double> randomZ{-10., 10.};
    cout << "\nPodaj liczbe losowanych punktow: ";
    double pointsInCuboid;
    cin >> pointsInCuboid;

    double pointsInBall;
    double pointsInCylinder;
    double ballVol = 0;
    double cylinderVol = 0;

    double x, y, z;     // wspolrzedne w 3D

    for(int i = 0; i < pointsInCuboid; ++i)
    {
        pointsInBall = 0;
        pointsInCylinder = 0;

        for(int j = 0; j < pointsInCuboid; ++j)
        {
            x = randomX(gen);
            y = randomY(gen);
            z = randomZ(gen);
            if(f(x, y, z) <= 100)   // wewnatrz kuli
            {
                pointsInBall++;
                if(g(x, y) <= 9 && z >= -3 && z <= 3)
                    pointsInCylinder++;
            }
        }
        ballVol += cuboidVol * (pointsInBall/pointsInCuboid)/pointsInCuboid;
        cylinderVol += cuboidVol * (pointsInCylinder/pointsInCuboid)/pointsInCuboid;
    }
    cout << "Objetosc tej bryly wynosi " << ballVol - cylinderVol << endl;
}

/// =====================================================================================

void integralApprox2(double a, double b, double (*f)(double))
{
    cout << "Podaj liczbe losowanych punktow: ";
    double pointsInRectangle;
    cin >> pointsInRectangle;

    double x, y;

    double max = 0;     // y - poziom gorny prostokata
    double min = 0;     // y - poziom dolny prostokata

    // wyznaczanie min i max
    x = a;
    for(int i{0}; i < pointsInRectangle; ++i)
    {
        x += (b-a) / pointsInRectangle;
        if(f(x) > max)
            max = f(x);
        if(f(x) < min)
            min = f(x);
    }

    double pointsOver0X  = 0;
    double pointsUnder0X = 0;

    double pointsOver0XUnderFx = 0;
    double pointsUnder0XOverFx = 0;

    // Pk = P * k/n, n - wszystkie proby, k - trafione
    double area = 0;
    double upperArea;
    double lowerArea;

    x = a;
    for(int j = 0; j < pointsInRectangle; j++)
    {
        x += (b-a) / pointsInRectangle;

        y = min;
        for(int i{0}; i < pointsInRectangle; ++i)
        {
            y += (max - min) / pointsInRectangle;
            if(y > 0)
            {
                ++pointsOver0X;
                if(y <= f(x))
                    ++pointsOver0XUnderFx;
            }
            else    // y < 0
            {
                ++pointsUnder0X;
                if(y >= f(x))
                    ++pointsUnder0XOverFx;
            }
        }
    }
    upperArea = (pointsOver0X > 0) ? max*(b-a)*pointsOver0XUnderFx/pointsOver0X : 0;
    lowerArea = (pointsUnder0X > 0)? min*(b-a)*pointsUnder0XOverFx/pointsUnder0X : 0; // jest to liczba ujemna, jako ze min < 0
    area = (upperArea + lowerArea);
    cout << "Pole liczone niezaleznie: " << area << endl;
}

void approxVolOfBall2(double (*f)(double, double, double))
{
    const double cuboidVol = 1000;
    // kula o promieniu 5
    cout << "\nPodaj liczbe losowanych punktow: ";
    double pointsInCuboid;
    cin >> pointsInCuboid;

    double pointsInBall = 0;
    double vol = 0;

    double x=-5, y=-5, z=-5;     // wspolrzedne w 3D

    for(int i = 0; i < pointsInCuboid; ++i)
    {
        x += (double)10 / pointsInCuboid;
        for(int j = 0; j < pointsInCuboid; ++j)
        {
            y += (double)10 / pointsInCuboid;
            for(int k = 0; k < pointsInCuboid; k++)
            {
                z += (double)10 / pointsInCuboid;
                if(f(x, y, z) <= 25)
                    pointsInBall++;
            }
            z = -5;
        }
        y = -5;
    }
    vol += (cuboidVol * pointsInBall) / (pointsInCuboid * pointsInCuboid * pointsInCuboid);
    cout << "Objetosc kuli o promieniu 5 wynosi " << vol << endl;
}

void approxVolOfCone2(double (*f)(double, double))
{
    const double cuboidVol = 4000;
    // stozek o promieniu ui wysokosci 10

    /*
    uniform_real_distribution <double> randomX{-10., 10.};
    uniform_real_distribution <double> randomY{-10., 10.};
    uniform_real_distribution <double> randomZ{0., 10.};    */

    cout << "\nPodaj liczbe losowanych punktow: ";
    double pointsInCuboid;
    cin >> pointsInCuboid;

    double pointsInCone = 0;
    double vol;

    double x=-10, y=-10, z=0;     // wspolrzedne w 3D

    for(int i = 0; i < pointsInCuboid; ++i)
    {
        x += (double)20 / pointsInCuboid;
        for(int j = 0; j < pointsInCuboid; ++j)
        {
            y += (double)20 / pointsInCuboid;
            for(int k = 0; k < pointsInCuboid; k++)
            {
                z += (double)10 / pointsInCuboid;
                if(z <= 10 - f(x, y))
                    pointsInCone++;
            }
            z = 0;
        }
        y = -10;
    }
    vol = (cuboidVol * pointsInCone) / (pointsInCuboid * pointsInCuboid * pointsInCuboid);
    cout << "Objetosc stozka o r=10, h=10 wynosi " << vol << endl;
}

void approxVolOf3dShape2(double (*f)(double, double, double), double (*g)(double, double))
{
    const double cuboidVol = 8000;
    // kula(R=10) - walec(H=6, r=3)
    cout << "\nPodaj liczbe losowanych punktow: ";
    double pointsInCuboid;
    cin >> pointsInCuboid;

    double pointsInBall = 0;
    double pointsInCylinder = 0;

    double x=-10, y=-10, z=-10;     // wspolrzedne w 3D

    for(int i = 0; i < pointsInCuboid; ++i)
    {
        x += (double)20 / pointsInCuboid;
        for(int j = 0; j < pointsInCuboid; ++j)
        {
            y += (double)20 / pointsInCuboid;
            for(int k = 0; k < pointsInCuboid; k++)
            {
                z += (double)20 / pointsInCuboid;
                if(f(x, y, z) <= 100)   // wewnatrz kuli
                {
                    pointsInBall++;
                    if(g(x, y) <= 9 && z >= -3 && z <= 3)
                        pointsInCylinder++;
                }
            }
            z = -10;
        }
        y = -10;
    }
    double ballVol = (cuboidVol * pointsInBall) / (pointsInCuboid * pointsInCuboid * pointsInCuboid);
    double cylinderVol = (cuboidVol * pointsInCylinder) / (pointsInCuboid * pointsInCuboid * pointsInCuboid);
    cout << "Objetosc tej bryly wynosi " << ballVol - cylinderVol << endl;
}
