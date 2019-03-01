#include <iostream>
#include <cmath>

using namespace std;

struct NodeBST
{
    int val;
    int sumL, sumR, leftSize;
    NodeBST * up;
    NodeBST * left;
    NodeBST * right;
    NodeBST(int _val, NodeBST * _up) : val(_val), sumL(0), sumR(0), leftSize(0), up(_up), left(nullptr), right(nullptr) {}
};

struct myPair
{
    bool isAVL;
    int height;
};

myPair isAVL(NodeBST * root, int a = INT_MIN, int b = INT_MAX)
{
    if(!root) return {true, 1};
    myPair left = isAVL(root->left, a, root->val);
    myPair right = isAVL(root->right, root->val, b);
    return {left.isAVL && right.isAVL && root->val > a && root->val < b
            && abs(left.height-right.height) <= 1, max(left.height, right.height)+1};
}

int findSum(NodeBST * root, int x, int y)
{
    int sum = root->val + root->sumL + root->sumR;
    NodeBST * curr = root;

    while(curr)
    {
        if(curr->val < x) {
            sum -= curr->val + curr->sumL;
            curr = curr->right;
        }
        else if(curr->val > x) {
            curr = curr->left;
        }
        else {
            sum -= curr->sumL;
            break;
        }
    }

    while(root)
    {
        if(root->val < y) {
            root = root->right;
        }
        else if(root->val > y) {
            sum -= root->val + root->sumR;
            root = root->left;
        }
        else {
            sum -= root->sumR;
            break;
        }
    }
    return sum;
}

int getNElement(NodeBST * root, int n)
{
    if(!root) return 0;
    if(n <= root->leftSize)
    {
        return getNElement(root->left, n);
    }
    else if(root->leftSize == n-1) return root->val;
    else return getNElement(root->right, n - root->leftSize - 1);
}

void inorder(NodeBST * node)
{
    if(!node) return;
    if(node->left) inorder(node->left);
    cout << node->val << ":" << node->sumL << ";" << node->sumR << "|" << node->leftSize << "   ";
    if(node->right) inorder(node->right);
}

bool insertBST(NodeBST * root, int key)
{
    NodeBST * curr = root;
    NodeBST * prev = root;

    while(curr && curr->val != key)
    {
        prev = curr;
        curr = (key < curr->val) ? curr->left : curr->right;
    }
    if(curr && curr->val == key) return false;

    NodeBST * newNode = new NodeBST(key, prev);
    if(key < prev->val)
    {
        prev->left = newNode;
        curr = prev->left;
    }
    else
    {
        prev->right = newNode;
        curr = prev->right;
    }

    while(prev)
    {
        if(prev->left == curr)
        {
            prev->leftSize++;
            prev->sumL += key;
        }
        else
        {
            prev->sumR += key;
        }

        curr = prev;
        prev = prev->up;
    }

    return true;
}

int main()
{
    /*
    NodeBST * node = new NodeBST(10, nullptr);
    insertBST(node, 5);
    insertBST(node, 15);
    insertBST(node, 7);
    insertBST(node, 13);
    insertBST(node, 1);
    inorder(node);

    cout << endl << "1. " << getNElement(node, 1);
    cout << endl << "2. " << getNElement(node, 2);
    cout << endl << "3. " << getNElement(node, 3);
    cout << endl << "4. " << getNElement(node, 4);
    cout << endl << "5. " << getNElement(node, 5);
    cout << endl << "6. " << getNElement(node, 6);
    */

    cout << "\nSum: ";
    int a, b;
    cin >> a >> b;

    NodeBST * bigTree = new NodeBST(24, nullptr);
    insertBST(bigTree, 13);
    insertBST(bigTree, 37);
    insertBST(bigTree, 7);
    insertBST(bigTree, 19);
    insertBST(bigTree, 29);
    insertBST(bigTree, 46);
    insertBST(bigTree, 4);
    insertBST(bigTree, 9);
    insertBST(bigTree, 16);
    insertBST(bigTree, 21);
    insertBST(bigTree, 26);
    insertBST(bigTree, 33);
    insertBST(bigTree, 41);
    insertBST(bigTree, 52);
    insertBST(bigTree, 2);
    insertBST(bigTree, 6);
    insertBST(bigTree, 8);
    insertBST(bigTree, 11);
    insertBST(bigTree, 14);
    insertBST(bigTree, 17);
    insertBST(bigTree, 20);
    insertBST(bigTree, 22);
    insertBST(bigTree, 25);
    insertBST(bigTree, 28);
    insertBST(bigTree, 31);
    insertBST(bigTree, 35);
    insertBST(bigTree, 43);
    insertBST(bigTree, 49);
    insertBST(bigTree, 57);

    cout << endl << findSum(bigTree, a, b);

    NodeBST * n = new NodeBST(10, nullptr);
    insertBST(n, 5);
    insertBST(n, 1);

    cout << "Sprawdzimy, czy jest AVL?\n";
    cout << ((isAVL(n).isAVL == true) ? "Jest AVL." : "Nie jest AVL.") ;
}

