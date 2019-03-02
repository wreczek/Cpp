#include <iostream>
#include <cmath>
using namespace std;

const double pi = 3.1415925;

void cubic_natural_spline(int n, double a, double b, double (*f)(double));
double ** createMatrix(int n, double h);
void GaussEliminationMethod(double ** M, int m);
void swapRows(double ** M, int m, int i);
void display(double ** M, int n);
double divDiff(int i, double * vals, double h);

int main()
{
    int n = 20;
    double * V = new double[n-2];
    double a = 0.1;
    double b = 1;
    double h = (b-a)/(double)(n-1);
    cubic_natural_spline(n, a, b, [](auto x){ return x*sin(pi/x); });
    /*
    cout << "Stopien: " << n << endl;
    for(int i = 0; i < n-2; i++)
        cout << i << ": " << V[i] << endl;
    */
    return 0;
}

void cubic_natural_spline(int n, double a, double b, double (*f)(double))
{
    double args[n];
    double vals[n];
    double h = (b-a)/(double)(n-1);
    for(int i = 0; i < n; i++)
    {
        args[i] = a+(double)i*h;
        vals[i] = f(args[i]);
        cout << i <<"("<<args[i]<<","<<vals[i]<<")\n";
    }
    double ** M = createMatrix(n-2, h);
    for(int i = 0; i < n-2; i++)  // tu zmiana
    {
        M[i][n-2] = 6*divDiff(i, vals, h);//dividedDifferencesHelper(i, n, args, vals);
    }

    GaussEliminationMethod(M, n-2);
    GaussEliminationMethod(M, n-2);

    double * V = new double[n-2];
    for(int i = 0; i < n-2; i++)
        V[i] = M[i][n-2];

    cout << "\nRozwiazanie:\n";
    cout << 0 << ": " << V[0]/h/6 << ", "<<0<<", "<<(vals[1]-vals[0])/h-h/6*V[0]<<", "<<vals[0]<<endl;;
    for(int i = 0; i < n-3; i++)
    {
        cout << i+1 << ": " << (V[i+1]-V[i])/h/6 << ", "<<V[i]/2<<", "<<(vals[i+2]-vals[i+1])/h - h/6*(V[i+1]+2*V[i])<<", "<<vals[i+1]<<endl;
    }
    cout << n-2 << ": " << -V[n-3]/h/6 << ", "<<V[n-3]/2<<", "<<(vals[n-1]-vals[n-2])/h-h/6*2*V[n-3]<<", "<<vals[n-2]<<endl;;
}

double ** createMatrix(int n, double h)
{
    double ** M = new double*[n];
    for(int i = 0; i < n; i++)
    {
        M[i] = new double[n+1];
        for(int j = 0; j < n+1; j++)
        {
            M[i][j] = 0;
            if(i==j) M[i][j] = 4*h;
            if(i-1 == j || i+1 == j) M[i][j] = h;
        }
    }

    return M;
}

void GaussEliminationMethod(double ** M, int m)
{
    double s;
    for(int i = 0; i < m; i++)
    {
        if(M[i][i] == 0)
                swapRows(M, m, i);
        for(int j = 0; j < m; j++)
        {
            if(j==i) continue;
            s = M[j][i]/M[i][i];
            for(int k = i; k < m+1; k++)
            {
                M[j][k] -= s*M[i][k];
            }
        }
    }
    for(int i = 0; i < m; i++)
    {
        M[i][m] /= M[i][i];
        M[i][i] = 1;
    }
}

void swapRows(double ** M, int m, int i)
{
    for(int j = i+1; j < m; j++)
    {
        if(M[j][i] != 0)
        {
            for(int k = 0; k < m+1; k++)
            {
                swap(M[i][k], M[j][k]);
            }
            return;
        }
    }
}

void display(double ** M, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

double divDiff(int i, double * vals, double h)
{
    return (vals[i+2]-vals[i+1])/h - (vals[i+1]-vals[i])/h;
}
