#include <iostream>
using namespace std;

const int m = 3;
const int n = 3;

struct Node
{
    bool val;
    Node * rep;
    int x, y;
    Node(bool _val, int wX, int wY) : val(_val), x(wX), y(wY), rep(nullptr) {}
};

Node * makeSet(bool val, int x, int y)
{
    Node * node = new Node(val, x, y);
    node->rep = node;
    return node;
}

Node * findSet(Node * x)
{
    if(x->rep != x)
        x->rep = findSet(x->rep);
    return x->rep;
}

void Union(Node * x, Node * y)
{
    x = findSet(x);
    y = findSet(y);
    if(x == y) return;
    x->rep = y;
}

int check(Node * arr[m][n], int x, int y)
{
    int count = 0;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(arr[i][j]->val && j + 1 < n && arr[i][j+1]->val)
                Union(arr[i][j], arr[i][j+1]);
            if(arr[i][j]->val && j - 1 >= 0 && arr[i][j-1]->val)
                Union(arr[i][j], arr[i][j-1]);
            if(arr[i][j]->val && i + 1 < m && arr[i+1][j]->val)
                Union(arr[i][j], arr[i+1][j]);
            if(arr[i][j]->val && i - 1 >= 0 && arr[i-1][j]->val)
                Union(arr[i][j], arr[i-1][j]);
        }
    }
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(findSet(arr[i][j]) == findSet(arr[y][x]))
                count++;
        }
    }
    return count-1;
}

void makeBoolArray(bool arr[m][n])
{
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            int val;
            cin >> val;
            if(val == 0)
                arr[i][j] = false;
            else
                arr[i][j] = true;
        }
    }
}

void makeNodeArray(bool tab[m][n], Node * arr[m][n])
{
    int val;
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
        {
            arr[i][j] = makeSet(tab[i][j], i, j);
        }
    }
}

int main()
{
    bool arr[m][n];
    Node * nodeArr[m][n];
    makeBoolArray(arr);
    makeNodeArray(arr, nodeArr);

    cout << "Podaj wspolrzedne punktu:\n> ";
    int wX, wY;
    cin >> wX;
    cin >> wY;
    cout << "Z punktu (" << wX << ", " << wY << ") jest osiagalne " << check(nodeArr, wX, wY) << " punktow.";
}
