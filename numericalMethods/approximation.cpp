#include <iostream>
#include <cmath>
#include <sstream>
#include <windows.h>

using namespace std;

const int prec = 3; // setprecision constant
const double eps = 1e-5;
const double pi = 3.14159;

double ** polynomialApproximation(double (*f)(double), double a, double b, int m, int n);
double ** trigonometricApproximation(double (*f)(double), double a, double b, int m, int n);
double ** createMatrix(int m);
void display(double ** M, int n);
void GaussEliminationMethod(double ** M, int m);
void swapRows(double ** M, int m, int i);
void writeOutputPolynomial(double ** M, string fun, int m, double a, double b);
void writeOutputTrigonometric(double ** M, string fun, int m, double a, double b);

int main()
{
    // rozna liczba punktow dyskretyzacji n
    // 1) n = 3 => 4 punkty
    /// suma kwadrat�w r�nic powinna by� jak najmniejsza
    // m - stopien wielomianu, wybieram sobie
    // na koncu wykresy oryginalne i aproksymowane i informacje o bledzie
    /// m < n !!! (m, n) = {(2,3),(2,4),(3,4),(3, 5)}
    /// 10+x*x/2-10*cos(2*x)
    /// -x*sin(sqrt(3*abs(x-1)))
    int m = 12;
    int n = 99; // punktow mamy n+1
    double a = -2*pi;
    double b = 2*pi;

    double ** M = polynomialApproximation([](auto x){ return 10+x*x/2-10*cos(2*x); }, a, b, m, n);
    //double ** M = trigonometricApproximation([](auto x){ return 10+x*x/2-10*cos(2*x); }, a, b, m, n);

    writeOutputPolynomial(M, "10+x*x/2-10*cos(2*x)", m, a, b);
    //writeOutputTrigonometric(M, "10+x*x/2-10*cos(2*x)", m, a, b);

    //double ** M = polynomialApproximation([](auto x){ return -x*sin(sqrt(3*abs(x-1))); }, a, b, m, n);
    //double ** M = trigonometricApproximation([](auto x){ return -x*sin(sqrt(3*abs(x-1))); }, a, b, m, n);

    //writeOutputPolynomial(M, "-x*sin(sqrt(3*abs(x-1)))", m, a, b);
    //writeOutputTrigonometric(M, "-x*sin(sqrt(3*abs(x-1)))", m, a, b);
    return 0;
}

double ** polynomialApproximation(double (*f)(double), double a, double b, int m, int n)
{
    double interval = (b-a) / (double)(n);
    double arg[n+1];
    double values[n+1];

    for(int i = 0; i <= n; i++)
    {
        arg[i] = a + (double)i*interval;   // odcieta
        values[i] = f(arg[i]);          // rzedna
    }

    double ** M = createMatrix(m);
    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <= m; j++)
        {

            for(int k = 0; k <= n; k++)
            {
                M[i][j] += pow(arg[k], i+j);
            }
        }
        for(int j = 0; j <= n; j++)
        {
            M[i][m+1] += values[j]*pow(arg[j], i);
        }
    }
    GaussEliminationMethod(M, m);
    GaussEliminationMethod(M, m); // eliminacja liczb typu e-015 w celu lepszej widocznosci
    display(M, m);
    return M;
}

double ** trigonometricApproximation(double (*f)(double), double a, double b, int m, int n)
{
    // m - stopien
    // n - liczba punktow
    double ** M = new double*[2];
    M[0] = new double[m+1];
    M[1] = new double[m+1];
    double X[n];

    for(int i=0; i<n; i++)
    {
        X[i]= pi*(double)i/((double)n/2);
    }

    for(int i=0; i<m+1; i++)
    {
        for(int j=0; j<n; j++)
        {
            M[0][i] += 1 /((double)n/2)*f(X[j])*cos(pi*(double)i*(double)j/((double)n/2));
            M[1][i] += 1 /((double)n/2)*f(X[j])*sin(pi*(double)i*(double)j/((double)n/2));
        }
    }
    M[0][0] /= (double)2;
    //B[0] = 0;

    cout << M[0][0] << " ";
    for(int i=1; i<m+1; i++)
    {
        cout << M[0][i] << "cos(" << i << "x)" << " ";
        cout << M[1][i] << "sin(" << i << "x)" << " ";
    }
    return M;
}

double ** createMatrix(int m)
{
    double ** M = new double*[m+1];
    for(int i = 0; i <= m; i++)
    {
        M[i] = new double[m+2];
        for(int j = 0; j <= m+1; j++)
        {
            M[i][j] = 0;
            //cin >> M[i][j];
        }
    }
    return M;
}

void display(double ** M, int m)
{
    cout << endl;
    for(int i = 0; i <= m; i++)
    {
        for(int j = 0; j <= m+1; j++)
        {
            cout << M[i][j] << " ";
        }
        cout << endl;
    }
}

void GaussEliminationMethod(double ** M, int m)
{
    double s;
    for(int i = 0; i <= m; i++)
    {
        if(M[i][i] == 0)
                swapRows(M, m, i);
        for(int j = 0; j <= m; j++)
        {
            if(j==i) continue;
            s = M[j][i]/M[i][i];
            for(int k = i; k <= m+1; k++)
            {
                M[j][k] -= s*M[i][k];
            }
        }
    }
    for(int i = 0; i <= m; i++)
    {
        M[i][m+1] /= M[i][i];
        M[i][i] = 1;
    }
}

void swapRows(double ** M, int m, int i)
{
    for(int j = i+1; j <= m; j++)
    {
        if(M[j][i] != 0)
        {
            for(int k = 0; k <= m+1; k++)
            {
                swap(M[i][k], M[j][k]);
            }
            return;
        }
    }
}

void writeOutputPolynomial(double **M,string fun,int m,double a,double b)
{
    double eps = 1e-6;
    string out_string;
    string out_D;
    string s = "plot " + fun + ", ";
    for(int i = 0; i < m+1; i++)
    {
        stringstream ss;
        ss << i;
        out_string = ss.str();

        double d = M[i][m+1];
        stringstream ss2;
        ss2 <<  d;
        out_D = ss2.str();

        cout <<  d << endl;

        if(i != 0 ){
            if(d >= 0 && abs(d) > eps)
                s+= "+";
        }
        if(abs(d) > eps)
            s += out_D+"*x^"+out_string;
    }

    out_string;
    stringstream ss;
    ss << a;
    out_string = ss.str();

    out_D;
    stringstream ss2;
    ss2 << b;
    out_D = ss2.str();


    s += ",x="+out_string+".."+out_D;
    cout << s << endl;

    const char* output = s.c_str();
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

void writeOutputTrigonometric(double ** M, string fun, int m, double a, double b)
{
    double eps = 1e-6;
    string s = "plot " + fun + ", ";
    stringstream first_ss;
    string out_A;
    string out_B;
    string print_i;
    if(abs(M[0][0]) > eps)
    {
        first_ss << ((M[0][0]));
        s += first_ss.str();
    }
    else
    {
        s += "0";
    }
    for(int i=1; i<m+1; i++)
    {
        stringstream ss;
        ss << i;
        print_i = ss.str();

        stringstream ss_A;
        ss_A << M[0][i];
        out_A = ss_A.str();

        stringstream ss_B;
        ss_B << M[1][i];
        out_B = ss_B.str();

        if(abs(M[0][i]) > eps)
        {
            if(M[0][i] >= 0) s += "+";
            s += out_A + "*cos(" + print_i + "*x)";
        }
        if(abs(M[1][i]) > eps)
        {
            if(M[1][i] >= 0) s += "+";
            s += out_B + "*sin(" + print_i + "*x)";
        }
    }

    string left_bound;
    stringstream ss_L;
    ss_L << a;
    left_bound = ss_L.str();

    string right_bound;
    stringstream ss_R;
    ss_R << b;
    right_bound = ss_R.str();


    s += ",x=" + left_bound + ".." + right_bound;
    cout << endl << s << endl;

    const char* output = s.c_str();
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}
