/*#include <iostream>
#include <cstring>
#include <ctime>
#include <random>
*/
#include <bits/stdc++.h>

using std::string;
using std::cin;
using std::cout;
using std::endl;

/// NODE
struct Node
{
    int val;
    Node ** forward;
    Node(const int _val, const int _lvl);
};

Node::Node(const int _val, const int _lvl) : val(_val)
{
    forward = new Node*[_lvl+1];
    memset(forward, 0, sizeof(Node*)*(_lvl+1));
}

/// SKIPLISTA
class SkipList
{
private:
    Node * header;
    int MAX_LVL;
    int lvl;
    float p;
public:
    SkipList(const int _max_lvl, const float _p);
    Node * createNode(const int _val, const int _lvl);
    int randomLevel();
    void insertElement(int x);
    void deleteElement(int x);
    void findElement(int x)const;
    void displaySkipList();
    void merge(SkipList & SL);
};

SkipList::SkipList(const int _max_lvl, const float _p) : MAX_LVL(_max_lvl), p(_p)
{
    lvl = 0;
    header = new Node(-1, MAX_LVL+1);
}

Node * SkipList::createNode(const int _val, const int _lvl)
{
    Node * node = new Node(_val, _lvl);
    return node;
}

int SkipList::randomLevel()
{
    int lvl = 0;
    float r = (float)rand() / RAND_MAX;
    while(p < r && lvl <= MAX_LVL)
    {
        lvl++;
        r = (float)rand() / RAND_MAX;
    }
    return lvl;
}

void SkipList::insertElement(int val)
{
    Node * update[MAX_LVL+1];
    memset(update, 0, sizeof(Node*)*(MAX_LVL+1));
    Node * curr = header;
    for(int i = lvl; i >= 0; i--)
    {
        while(curr -> forward[i] != NULL && val > curr -> forward[i] -> val)
        {
            curr = curr -> forward[i];
        }
        update[i] = curr;
    }
    curr = curr -> forward[0];

    if(curr == NULL || curr -> val != val)
    {
        int r = randomLevel();
        if(r > lvl)
        {
            for(int i = lvl; i <= r; i++)
            {
                update[i] = header;
            }
            lvl = r;
        }
        Node * n = createNode(val, r);

        for(int i = 0; i <= r; i++)
        {
            n -> forward[i] = update[i] -> forward[i];
            update[i] -> forward[i] = n;
        }
        cout << "Successfully added " << val << " to SkipList.\n";
    }
}

void SkipList::deleteElement(int val)
{
    Node * curr = header;
    Node * update[lvl+1];
    memset(update, 0, sizeof(Node*)*(lvl+1));
    for(int i = lvl; i >= 0; i--)
    {
        while(curr -> forward[i] != NULL && val > curr -> forward[i] -> val)
        {
            curr = curr -> forward[i];
        }
        update[i] = curr;
    }
    curr = curr -> forward[0];

    if(curr != NULL && curr -> val == val)
    {
        for(int i = 0; i <= lvl; i++)
        {
            if(update[i] -> forward[i] != curr) break;
            update[i] -> forward[i] = curr -> forward[i];
        }
        delete [] curr;
        cout << "Successfully deleted " << val << " from SkipList.\n";
    }
}

void SkipList::findElement(int val)const
{
    Node * curr = header;
    for(int i = lvl; i >= 0; i--)
    {
        while(curr -> forward[i] != NULL && val > curr -> forward[i] -> val)
        {
            curr = curr -> forward[i];
        }
        if(curr -> forward[i] != NULL && curr -> forward[i] -> val == val)
        {
            cout << "Found " << val << " in SkipList.\n";
            return;
        }
    }
    curr = curr -> forward[0];

    if(curr != NULL && curr -> val == val)
    {
        cout << "Found " << val << " in SkipList.\n";
    }
    else
    {
        cout << "Didn't find " << val << " in SkipList.\n";
    }
}

void SkipList::displaySkipList()
{
    Node * curr = header;
    for(int i = lvl; i >= 0; i--)
    {
        cout << endl << i << ": ";
        curr = header;
        while(curr -> forward[i] != NULL)
        {
            curr = curr -> forward[i];
            cout << curr -> val << " ";
        }
    }
}

void SkipList::merge(SkipList & SL);

int main()
{
    srand(time(NULL));
    SkipList SL(3, 0.5);
    SL.insertElement(5);
    SL.insertElement(1);
    SL.insertElement(9);
    SL.insertElement(14);
    SL.insertElement(21);
    SL.insertElement(17);
    SL.insertElement(8);
    SL.insertElement(2);
    SL.insertElement(14);
    SL.displaySkipList();
    SL.deleteElement(9);
    SL.displaySkipList();
}
