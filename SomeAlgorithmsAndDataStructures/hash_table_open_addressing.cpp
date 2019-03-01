#include <iostream>
#include <string.h>

using namespace std;

typedef unsigned int hashT;

enum State
{
    wolny,
    zajety,
    usuniety
};

struct Node
{
    char * pesel;
    State state;
    Node(char * _pesel) : pesel(_pesel), state(wolny) {}
};

struct HashTable
{
    int size;
    Node ** array;
    HashTable(int _size);
    bool insert(Node * n);
    bool remove(Node * n);
    void print();
};

HashTable::HashTable(int _size) : size(_size)
{
    array = new Node*[size];
    memset(array, 0, sizeof(Node)*(size));
}

hashT getHash(Node * n)
{
    hashT index = 0;
    int x = 65539;
    for(int i = 0; n->pesel[i] != 0; i++)
    {
        index = index * x + n->pesel[i];
    }
    return index*x;
}

bool HashTable::insert(Node * n)
{
    hashT index = getHash(n) % size;
    hashT getStart = index;
    /*  // chyba niepotrzebne?
    if(array[index] == NULL)
    {
        array[index] = n;
        array[index]->state = zajety;
        return true;
    }
    */
    while(array[index] != NULL && array[index]->state == zajety)
    {
        index++;
        index %= size;
        if(getStart == index) return false;
    }
    array[index] = n;
    array[index]->state = zajety;
    return true;
}

bool HashTable::remove(Node * n)
{
    hashT index = getHash(n)%size;
    hashT getStart = index;
    if(array[index] == NULL) return false;
    while(array[index] != NULL && array[index]->state != wolny)
    {
        if(array[index]->pesel == n -> pesel)
        {
            array[index]->state = usuniety;
            return true;
        }
        index++;
        index %= size;
        if(index == getStart) return false;
    }
    return false;
}

void HashTable::print()
{
    for(int i = 0; i < size; i++)
    {
        if(array[i] == NULL || array[i]->state == usuniety || array[i]->state == wolny) continue;
        cout << array[i] -> pesel << endl;
    }
}

int main()
{
    HashTable ht(10);
    Node * n1 = new Node("12345");
    Node * n2 = new Node("54321");
    Node * n3 = new Node("6565");
    Node * n4 = new Node("5656");
    Node * n5 = new Node("12378632");
    Node * n6 = new Node("3890482");
    Node * n7 = new Node("1604");
    Node * n8 = new Node("0708");
    Node * n9 = new Node("2111");
    cout << "PESEL " << n1->pesel << " HASH " << getHash(n1) << ", mod " << getHash(n1) % ht.size << endl;
    cout << "PESEL " << n2->pesel << " HASH " << getHash(n2) << ", mod " << getHash(n2) % ht.size << endl;
    cout << "PESEL " << n3->pesel << " HASH " << getHash(n3) << ", mod " << getHash(n3) % ht.size << endl;
    cout << "PESEL " << n4->pesel << " HASH " << getHash(n4) << ", mod " << getHash(n4) % ht.size << endl;
    cout << "PESEL " << n5->pesel << " HASH " << getHash(n5) << ", mod " << getHash(n5) % ht.size << endl;
    cout << "PESEL " << n6->pesel << " HASH " << getHash(n6) << ", mod " << getHash(n6) % ht.size << endl;
    cout << "PESEL " << n7->pesel << " HASH " << getHash(n7) << ", mod " << getHash(n7) % ht.size << endl;
    cout << "PESEL " << n8->pesel << " HASH " << getHash(n8) << ", mod " << getHash(n8) % ht.size << endl;
    cout << "PESEL " << n9->pesel << " HASH " << getHash(n9) << ", mod " << getHash(n9) % ht.size << endl;
    cout << n1->state << endl;
    ht.insert(n1);
    ht.insert(n2);
    ht.insert(n3);
    ht.insert(n4);
    ht.insert(n5);
    ht.insert(n6);
    ht.insert(n7);
    ht.insert(n8);
    ht.insert(n9);
    ht.print();

    ht.remove(n1);
    ht.remove(n3);
    ht.remove(n6);
    ht.insert(n3);
    ht.insert(n1);
    ht.remove(n7);
    ht.insert(n7);
    ht.insert(n6);
    cout << endl << endl << "Po usunieciu:\n";

    ht.print();
}
