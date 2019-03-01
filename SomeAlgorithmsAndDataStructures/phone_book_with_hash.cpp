#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

struct Node
{
    char * firstName;
    char * lastName;
    char * phone;
    int age;
    Node * next;
    Node(char * firstName, char * lastName, char * phone, int age);
};

Node::Node(char * _firstName, char * _lastName, char * _phone, int _age)
          : firstName(_firstName)
          , lastName(_lastName)
          , phone(_phone)
          , age(_age)
          , next(NULL) {}

struct HashTable
{
    int size;
    Node ** array;
    HashTable(int size);
};

HashTable::HashTable(int size)
{
    this->size = size;
    array = new Node*[size];
    memset(array, 0, sizeof(Node*)*(size));
}

int getHash(Node * item)
{
    int index = 0;
    int x = 11;//65599;
    for(int i = 0; item->firstName[i] != 0; i++)
    {
        index = index*x + item->firstName[i];
    }
    for(int i = 0; item->lastName[i] != 0; i++)
    {
        index = index*x + item->lastName[i];
    }
    return index*x + item->age;
}

void insert(HashTable * ht, Node * n)
{
    int index = getHash(n)%ht->size;
    n->next = ht->array[index];
    ht->array[index] = n;
}

char * find(HashTable * ht, char * firstName, char * lastName, int age){
    Node * n = new Node(firstName, lastName, NULL, age);
    int index = getHash(n)%ht->size;
    Node * current = ht->array[index];
    while(current)
    {
        if(current->lastName == lastName)
        {
            cout << "--------FOUND--------\n";
            cout << "firstName = " << current->firstName<<", lastName = " <<
                    current->lastName<<", phone = "<<// current->phone <<
                    ", age = " << current->age << endl;
            cout << "----------------------\n";
            return current->phone;
        }
        current = current->next;
    }
    cout << "Phone not found.";
    return NULL;
}

void printPhoneBook(HashTable * ht){
    cout << "ht->size=" << ht->size << endl;
    int size = ht->size;
    Node * curr;
    int j = 1;
    for(int i = 0; i < size; i++)
    {
        cout << "i="<<i<<endl;
        curr = ht->array[i];

        while(curr)
        {
            cout << j++ << ". " << curr->firstName << " " << curr->lastName << ", "
                 << curr->phone << ", " << curr->age << endl;
            curr = curr->next;
        }
    }
}
Node * remove(HashTable * ht, char * firstName, char * lastName, int age)
{
    Node * n = new Node(firstName, lastName, NULL, age);
    int index = getHash(n)%ht->size;
    Node * curr = ht->array[index];
    Node * prev = curr;
    while(curr->lastName != NULL && curr->lastName != lastName)
    {
        prev = curr;
        curr = curr -> next;
    }
    if(curr == prev)
    {
        ht->array[index]=curr->next;
    }
    else
    {
        prev->next=curr->next;
    }
    curr->next = NULL;
    return curr;
}


int main()
{
    Node * p1 = new Node("Wiktor", "Reczek", "794370551", 21);
    Node * p2 = new Node("Mateusz", "Reczek", "534604076", 17);
    Node * p3 = new Node("Krystian", "Krakowski", "666997112", 20);
    Node * p4 = new Node("Jakub", "Twardy", "503350028", 18);
    Node * p5 = new Node("Szymon", "Mazur", "999999999", 23);


    HashTable * ht = new HashTable(2);

    insert(ht, p1);
    insert(ht, p2);
    insert(ht, p3);
    insert(ht, p4);
    insert(ht, p5);

    cout << "Wiktor's phone: " << find(ht, "Wiktor", "Reczek", 21) << endl << endl;
    cout << "Matthew's phone: " << find(ht, "Mateusz", "Reczek", 17) << endl << endl;
    cout << "Cristian's phone: " << find(ht, "Krystian", "Krakowski", 20) << endl << endl;
    cout << "Jacob's phone: " << find(ht, "Jakub", "Twardy", 18) << endl << endl;
    cout << "Simon's phone: " << find(ht, "Szymon", "Mazur", 23) << endl << endl << endl;

    printPhoneBook(ht);

    cout << "Wiktor's phone: " << find(ht, "Wiktor", "Reczek", 21) << endl;
}
