#include <iostream>
#include <string>
using namespace std;

const int howMany = 9;

struct Node
{
    int p;
    char ch;
    Node * left;
    Node * right;
    Node * up;
    Node(int _p, char _ch) : p(_p), ch(_ch), left(nullptr), right(nullptr), up(nullptr) {}
};

void sortNodes(Node * tab[], int n, int k)
{
    for(int i = n-1; i > k; i--)
    {
        if(tab[i]->p < tab[i-1]->p)
        {
            swap(tab[i], tab[i-1]);
        }
    }
}

Node * makeTree(Node * tab[], int n)
{
    for(int i = 0; i < n-1; i++)
    {
        sortNodes(tab, n, i);   sortNodes(tab, n, i);   // wyciagamy dwie najmniejsze liczby, stad dwa wywolania
        Node * tree = new Node(tab[i]->p+tab[i+1]->p, '\0');
        tree->left = tab[i];     tree->left ->up = tree;
        tree->right = tab[i+1];  tree->right->up = tree;
        tab[i+1] = tree;
    }
    return tab[n-1];
}

void makeArray(Node * root, string * arr, int n)
{
    int top = 0;
    Node * tab[n];
    Node * curr = root;
    string result = "";
    while(top >= 0)
    {
        if(curr->left)
        {
            tab[top++] = curr;
            curr = curr->left;
            result += "0";
        }
        else
        {
            arr[(curr->ch - (int)('A'))] = result;
            Node * parent = tab[--top];
            if(top < 0) return;
            while(curr != parent)
            {
                result.erase(result.begin() + result.size()-1);
                curr = curr->up;
            }
            curr = curr->right;
            result += '1';
        }
    }
}

string encode(Node * root, string exp)
{
    string arr[howMany];
    makeArray(root, arr, howMany);
    Node * curr;
    string result = "";
    for(int i = 0; i < exp.size(); i++)
    {
        result += arr[(exp[i] - (int)('A'))];
    }
    return result;
}

string decode(Node * root, string exp)
{
    Node * curr;
    string result = "";
    for(int i = 0; exp[i] != 0; i++)
    {
        curr = root;
        while(curr)
        {
            if(exp[i] == '0')
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
            if(curr->ch != 0) break;
            else i++;
        }
        result += curr->ch;
    }
    return result;
}

void printTree(Node * root)
{
    if(!root) return;
    if(root->left) printTree(root->left);
    cout << root->ch << "|" << root->p << "  ";
    if(root->right) printTree(root->right);
}

int main()
{
    /**
    /*
    Node * n1 = new Node(3, 'C');
    Node * n2 = new Node(2, 'B');
    Node * n3 = new Node(1, 'A');
    Node * n4 = new Node(4, 'D');
    Node * nodes[howMany] = {n3, n2, n1, n4};
    //to samo co wyzej ale petla
    // * /

    Node * nodes[howMany];
    for(int i = 0; i < howMany; i++)
    {
        nodes[i] = new Node(howMany-i, (char)('D'-i));
        //nodes[i] = new Node(i+1, (char)('A'+i));
    }

    Node * root = makeTree(nodes, howMany);
    printTree(root);

    cout << "\nencode(CBAD): " << encode(root, "CBAD") << endl;
    cout << "decode(0010011000): " << decode(root, "0010011000") << endl;
    cout << "\nADBACBDBCADCACACBA = " << decode(root, encode(root, "ADBACBDBCADCACACBA"));

    cout << "\nTEST:\n";
    cout << "decode(1001100101101100111001010100) = " << decode(root, "1001100101101100111001010100") << endl;
    cout << "encode('A'): " << encode(root, "A") << endl;
    cout << "encode('B'): " << encode(root, "B") << endl;
    cout << "encode('C'): " << encode(root, "C") << endl;
    cout << "encode('D'): " << encode(root, "D") << endl;
    **/

    Node * n1 = new Node(1, 'A');
    Node * n2 = new Node(1, 'B');
    Node * n3 = new Node(1, 'C');
    Node * n4 = new Node(1, 'D');
    Node * n5 = new Node(2, 'E');
    Node * n6 = new Node(2, 'F');
    Node * n7 = new Node(3, 'G');
    Node * n8 = new Node(4, 'H');
    Node * n9 = new Node(5, 'I');

    Node * nodes[howMany] = {n3, n4, n1, n2, n5, n6, n7, n8, n9};

    Node * root = makeTree(nodes, howMany);

    cout << "encode(A) = " << encode(root, "A") << endl;
    cout << "encode(B) = " << encode(root, "B") << endl;
    cout << "encode(C) = " << encode(root, "C") << endl;
    cout << "encode(D) = " << encode(root, "D") << endl;
    cout << "encode(E) = " << encode(root, "E") << endl;
    cout << "encode(F) = " << encode(root, "F") << endl;
    cout << "encode(G) = " << encode(root, "G") << endl;
    cout << "encode(H) = " << encode(root, "H") << endl;
    cout << "encode(I) = " << encode(root, "I") << endl << endl;

    cout << "encode(BACABIEDA) = " << encode(root, "BACABIEDA") << endl;
    cout << "ABDCAIEFGHAIFBAGC ?= " << decode(root, encode(root, "ABDCAIEFGHAIFBAGC")) << endl << endl;

    cout << "\n\nPodaj swoj wlasny szyfr:\n> ";
    string szyfr;
    cin >> szyfr;
    cout << "\nPo deszyfrowaniu:\n> ";
    cout << decode(root, szyfr);

    cout << "\n\nA teraz podaj wyraz, a ja go zaszyfruje:\n> ";
    cin >> szyfr;
    cout << "\nPo zaszyfrowaniu:\n> ";
    cout << encode(root, szyfr);
}
