#include <iostream>
#include <string.h>
using namespace std;

enum State
{
    //free,
    occupied,
    deleted
};

struct Node
{
    string name;
    int age;
    State state;
};

struct HashTable
{
    int size;
    Node ** array;
};

Node * createNode(string name, int age)
{
    Node * node = new Node;
    node->name = name;
    node->age = age;
    node->state = occupied;
    return node;
}

struct HashTable
{
    int size;
    Node ** array;
};

HashTable * createHashTable(int size)
{
    HashTable * HT = new HashTable;
    HT->size = size;
    HT->array = new Node*[size];
    memset(HT->array, 0, sizeof(Node*)*(size));
    return HT;
}

int getHash(string name, int age)
{
    int x = 41;
    int index = 0;
    for(int i = 0; i < name.size(); i++)
    {
        index = index * x + i;
    }
    index = index * x + age;
    return index;
}

Node * find(HashTable * HT, string name, int age)
{
    int size = HT->size;
    int index = getHash(name, age) % size;
    Node * curr;
    for(int i = 0; i < size; i++)
    {
        index %= size;
        if(!HT->array[index]) return nullptr;

        curr = HT->array[index];
        if(curr->state == occupied)
        {
            if(curr->name == name && curr->age == age)
            {
                return curr;
            }
        }
        index++;
    }
}

bool insert(HashTable * HT, string name, int age)
{
    int size = HT->size;
    int i = 0;
    int index = getHash(name, age) % size;
    Node * curr = HT->array[index];
    Node * node = createNode(name, age);
    while(curr && i < size)
    {
        if(curr->state == deleted)
        {
            //curr = node;
            HT->array[index] = node;
            return true;
        }
        if(curr->name == name && curr->age == age)
        {
            return false;
        }
        index = (index+1)%HT->size;
        curr = HT->array[index];
        i++;
    }
    if(!curr)
    {
        HT->array[index] = node;
        return true;
    }
    return false;
}

bool remove(HashTable * HT, string name, int age)
{
    int i = 0;
    int size = HT->size;
    int index = getHash(name, age) % size;
    Node * curr = HT->array[index];
    while(curr && i < size)
    {
        if(curr->state == occupied)
        {
            if(curr->name == name && curr->age == age)
            {
                curr->state = deleted;
                return true;
            }
        }
        index = (index+1) % size;
        curr = HT->array[index];
        i++;
    }
    return false;
}

void displayNode(Node * node)
{
    cout << endl << "The person is " << node->name;
    cout << ", " << node->age;
}

void displayHashTable(HashTable * HT)
{
    int size = HT->size;
    Node * curr;
    for(int i = 0; i < size; i++)
    {
        curr = HT->array[i];
        if(curr && curr->state == occupied)
        {
            cout << i << ". " << HT->array[i]->name << ", " << HT->array[i]->age << endl;
        }
    }
}

int main()
{
    HashTable * HT = createHashTable(20);
    insert(HT, "Wiktor", 21);
    insert(HT, "Mateusz", 18);
    insert(HT, "Sara", 20);
    insert(HT, "Lukasz", 20);
    insert(HT, "Barbara", 47);
    insert(HT, "Wiktor", 20);
    insert(HT, "Wiktor", 20);
    insert(HT, "Rotkiw", 21);
    displayHashTable(HT);
    /*
    cout << "\nFind person:\nName: ";
    string name;
    cin >> name;
    cout << "Age: ";
    int age;
    cin >> age;
    displayNode(find(HT, name, age));
    */
    cout << "\nRemove person:\nName: ";
    string name;
    cin >> name;
    cout << "Age: ";
    int age;
    cin >> age;
    if(remove(HT, name, age)) cout << "\nDeleted.\n";
    else                      cout << "\nFailure.\n";
    displayHashTable(HT);

    cout << "\nInsert person:\nName: ";
    cin >> name;
    cout << "Age: ";
    cin >> age;
    insert(HT, name, age);
    displayHashTable(HT);
}

