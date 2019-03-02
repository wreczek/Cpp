#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

const double eps = 1e-3;

double * createVector(int n);
double ** createMatrix(int n);
double * jacobi(double ** A, double * b, int n);
double * gaussSeidel(double ** A, double * b, int n);
double ** generateUnitMatrix(int n);
double * subtractVectors(double * A, double * B, int n);
double * multiplyMatrixByVector(double ** A, double * x, int n);
double ** inversion(double ** A, int n);
double ** createMatrixOfDiagonal(double ** A, int n);
double ** resetDiagonal(double ** A, int n);
double ** antiU(double ** A, int n);
double ** fU(double ** A, int n);
void displayVector(double * x, int n);
double ** ludist(double ** A, int n);
void lusolve(double ** A, double ** x, int n, int k);
void displayMatrix(double ** A, int n);
double ** generateMatrix(int n);
double * generateVector(int n);
double ** generateLaplasjan(int n);

int main()
{
    srand(time(NULL));
    int n;
    cin >> n;
    double ** A = createMatrix(n);

    double * b = createVector(n);
    //double ** A = generateMatrix(n);
    //double ** A = generateLaplasjan(n);
    //double * b = generateVector(n);
    double * x1 = jacobi(A, b, n);
    //displayVector(x1, n);

    cout << endl;
    //double * x2 = gaussSeidel(A, b, n);
    displayVector(x1, n);
    return 0;
}

double * createVector(int n)
{
    double * x = new double[n];
    for(int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    return x;
}

double ** createMatrix(int n)
{
    double ** x = new double*[n];
    for(int i = 0; i < n; i++)
    {
        x[i] = new double[n];
        for(int j = 0; j < n; j++)
            cin >> x[i][j];
    }
    return x;
}

double * jacobi(double ** A, double * b, int n)
{
    // C - macierz z zerowa przekatna (zbudowana z A)
    // D - macierz diagonalna z przekatna z A, reszta 0
    double ** C = resetDiagonal(A, n);
    double ** D = createMatrixOfDiagonal(A, n);
    double * x = new double[n];
    for(int i = 0; i < n; i++)
        x[i] = 1;

    int i;
    bool flag;
    for(i = 0; i < 50000; i++)
    {
        flag = true;    // koniec
        x = multiplyMatrixByVector(inversion(D, n),
            subtractVectors(b, multiplyMatrixByVector(C, x, n), n), n);
        double * check = multiplyMatrixByVector(A, x, n);
        for(int j = 0; j < n; j++)
            if(abs(check[j] - b[j]) > eps)
                flag = false;
        if(flag)
            break;
    }
    cout << "Jacobi wykonal " << i << " krokow.\n";
    return x;
/*
    P(D^-1 * C) < 1 - warunek
    2 1 1 7
    1 2 1 8
    1 1 2 9
*/
}

double * gaussSeidel(double ** A, double * b, int n)
{
    // D - macierz diagonalna z przekatna z A, reszta 0
    // L - lower of A
    // U - upper of A

    double * x = new double[n];
    for(int i = 0; i < n; i++)
        x[i] = 1;
    double ** D = createMatrixOfDiagonal(A, n);
    double ** U = fU(A, n);
    double ** T = antiU(A, n);

    int i;
    bool flag;
    for(i = 0; i < 50000; i++)
    {
        flag = true;
        x = multiplyMatrixByVector(inversion(T, n),
            subtractVectors(b, multiplyMatrixByVector(U, x, n), n), n);
            double * check = multiplyMatrixByVector(A, x, n);
        for(int j = 0; j < n; j++)
            if(abs(check[j] - b[j]) > eps)
                flag = false;
        if(flag)
            break;
    }
    cout << "Gauss_Seidel wykonali " << i << " krokow.\n";
    return x;
}

double ** generateUnitMatrix(int n)
{
    double ** x = new double*[n];
    for(int i = 0; i < n; i++)
    {
        x[i] = new double[n];
        for(int j = 0; j < n; j++)
            if(i == j)
                x[i][i] = 1;
            else
                x[i][j] = 0;
    }
    return x;
}

double * subtractVectors(double * A, double * B, int n)
{
    double * x = new double[n];
    for(int i = 0; i < n; i++)
        x[i] = A[i] - B[i];
    return x;
}


double * multiplyMatrixByVector(double ** A, double * x, int n)
{
    double * y = new double[n];
    for(int i = 0; i < n; i++)
    {
        y[i] = 0;
        for(int j = 0; j < n; j++)
            y[i] += A[i][j] * x[j];
    }
    return y;
}

double ** inversion(double ** A, int n)
{
    double ** luA = ludist(A, n);
    double ** x = new double*[n];   // macierz jednostkowa
    for(int i = 0; i < n; i++)
    {
        x[i] = new double[n];
        for(int j = 0; j < n; j++)
            x[i][j] = 0;
        x[i][i] = 1;
    }
    for(int i = 0; i < n; i++)
        lusolve(luA, x, n, i);
    return x;
}

double ** createMatrixOfDiagonal(double ** A, int n)
{
    double ** B = new double*[n];
    for(int i = 0; i < n; i++)
    {
        B[i] = new double[n];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                B[i][i] = A[i][i];
            else
                B[i][j] = 0;
        }
    }
    return B;
}

double ** resetDiagonal(double ** A, int n)
{
    double ** B = new double*[n];
    for(int i = 0; i < n; i++)
    {
        B[i] = new double[n];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                B[i][i] = 0;
            else
                B[i][j] = A[i][j];
        }
    }
    return B;
}

double ** fU(double ** A, int n)
{
    double ** B = new double*[n];
    for(int i = 0; i < n; i++)
    {
        B[i] = new double[n];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i < j)
                B[i][j] = A[i][j];
            else
                B[i][j] = 0;
        }
    }
    return B;
}

double ** antiU(double ** A, int n)
{
    double ** B = new double*[n];
    for(int i = 0; i < n; i++)
    {
        B[i] = new double[n];
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i >= j)
                B[i][j] = A[i][j];
            else
                B[i][j] = 0;
        }
    }
    return B;
}

void displayVector(double * x, int n)
{
    for(int i = 0; i < n; i++)
        cout << "x" << i+1 << " = " << x[i] << endl;
}

double ** ludist(double ** A, int n)
{
    double ** x = new double*[n];
    for(int i = 0; i < n; i++)
    {
        x[i] = new double[n];
        for(int j = 0; j < n; j++)
            x[i][j] = A[i][j];
    }
    for(int k = 0; k < n-1; k++)
    {
        for(int i = k+1; i < n; i++)
            x[i][k] /= x[k][k];
        for(int i = k+1; i < n; i++)
            for(int j = k+1; j < n; j++)
                x[i][j] -= x[i][k] * x[k][j];
    }
    return x;
}

void lusolve(double ** A, double ** X, int n, int k)
{
    double s;
    for(int i = 1; i < n; i++)
    {
        s = 0;
        for(int j = 0; j < i; j++)
            s += A[i][j] * X[j][k];
        X[i][k] -= s;
    }
    X[n-1][k] /= A[n-1][n-1];
    for(int i = n-2; i >= 0; i--)
    {
        s = 0;
        for(int j = i+1; j < n; j++)
            s += A[i][j] * X[j][k];
        X[i][k] = (X[i][k] - s) / A[i][i];
    }
}

void displayMatrix(double ** A, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}

double ** generateMatrix(int n)
{
    double ** A = new double*[n];
    for(int i = 0; i < n; i++)
    {
        A[i] = new double[n];
        for(int j = 0; j < n; j++)
            A[i][j] = rand() % 19 - 9;
    }
    return A;
}

double * generateVector(int n)
{
    double * b = new double[n];
    for(int i = 0; i < n; i++)
    {
        b[i] = rand() % 101 - 50;
    }
    return b;
}

double ** generateLaplasjan(int n)
{
    double ** A = new double*[n];
    for(int i = 0; i < n; i++)
    {
        A[i] = new double[n];
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                A[i][i] = 2;
            else if(i+1 == j || i-1 == j)
                A[i][j] = -1;
            else
                A[i][j] = 0;
        }
    }
    return A;
}
