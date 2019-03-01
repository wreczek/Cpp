#include <iostream>
#include <string.h>
using namespace std;

struct Node
{
    string name;
    int age;
    Node * next;
};

Node * createNode(string name, int age)
{
    Node * node = new Node;
    node->name = name;
    node->age = age;
    node->next = nullptr;
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
        index = x * index + name[i];
    }
    index = x * index + age;
    return index;
}

bool insert(HashTable * HT, string name, int age)
{
    Node * node = createNode(name, age);
    int index = getHash(name, age) % HT->size;
    if(!HT->array[index])
    {
        HT->array[index] = node;
        return true;
    }
    Node * curr = HT->array[index];
    Node * prev;
    while(curr)
    {
        prev = curr;
        if(curr->name == node->name && curr->age == node->age) return false;
        curr = curr->next;
    }
    prev->next = node;
    return true;
}

Node * find(HashTable * HT, string name, int age)
{
    int index = getHash(name, age) % HT->size;
    Node * curr = HT->array[index];
    while(curr)
    {
        if(curr->name == name && curr->age == age)
        {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

bool remove(HashTable * HT, string name, int age)
{
    int index = getHash(name, age) % HT->size;
    Node * curr = HT->array[index];
    Node * prev;
    while(curr)
    {
        if(curr->name == name && curr->age == age)
        {
            if(curr == HT->array[index]) HT->array[index] = HT->array[index]->next;
            else prev->next = curr->next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
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
    Node * curr;
    for(int i = 0; i < HT->size; i++)
    {
        curr = HT->array[i];
        while(curr)
        {
            cout << curr->name << ", " << curr->age << endl;
            curr = curr->next;
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
}
