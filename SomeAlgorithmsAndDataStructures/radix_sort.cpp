#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void swap(int * num1, int * num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int getMax(int tab[], int n)
{
    int mx = tab[0];
    for(int i = 1; i < n; i++)
    {
        if(tab[i] > mx)
            mx = tab[i];
    }
    return mx;
}

void create_tab(int tab[], int n)
{
    for(int i = 0; i < n; i++)
    {
        tab[i] = rand();
    }
}

void print_tab(int tab[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << tab[i] << " " << endl;
    }
}

void count_sort(int A[], int n, int exp)
{
    int B[10] = {0};
    int C[n];
    for(int i = 0; i < n; i++)
    {
        B[(A[i]/exp)%10]++;
    }
    for(int i = 1; i < 10; i++)
    {
        B[i] += B[i-1];
    }
    for(int i = n-1; i >= 0; i--)
    {
        C[--B[(A[i]/exp)%10]] = A[i];
    }
    for(int i = 0; i < n; i++)
    {
        A[i] = C[i];
    }
}

void radix_sort(int tab[], int n)
{
    int m = getMax(tab, n);
    for(int exp = 1; m/exp > 0; exp *= 10)
    {
        count_sort(tab, n, exp);
    }
}
/*
void bubble_sort(int tab[], int n)  // dla porownania - bubble ssie xd
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(tab[j] > tab[j+1])
                swap(&tab[j], &tab[j+1]);
        }
    }
}
*/
/*      radix minimalnie szybszy od iteracyjnego quick sorta
int partition(int tab[], int l, int r){
    int i = l;
    int pivot = tab[r];
    for(int j = l; j <= r-1; j++)
    {
        if(tab[j] <= pivot)
        {
            swap(&tab[j], &tab[i]);
            i++;
        }
    }
    swap(&tab[i], &tab[r]);
    return i;
}

void quick_sort(int tab[], int l, int r)
{
   int stack[r-l+1];
   int top = -1;

   stack[++top] = l;        // 0 left
   stack[++top] = r;        // 1 right

   while(top >= 0)
   {
       r = stack[top--];
       l = stack[top--];

       int p = partition(tab, l, r);

       if(p - 1 > l)
       {
           stack[++top] = l;
           stack[++top] = p-1;
       }
       if(p + 1 < r)
       {
           stack[++top] = p+1;
           stack[++top] = r;
       }
   }
}
*/
int main()
{
    srand(time(NULL));
    int n;
    cin >> n;
    int tab[n];
    create_tab(tab, n);
    //print_tab(tab, n);
    cout << endl;
    //radix_sort(tab, n);
    quick_sort(tab, 0, n-1);
    //bubble_sort(tab, n);
    //print_tab(tab, n);
}
