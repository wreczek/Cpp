#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "Exception.h"

template <class T>
class Node
{
private:
    T val;
    Node<T> * next;
public:
    Node(T _val, Node<T> * node) : val(_val), next(node) {}
    ~Node() { delete next; }
    void setNext(Node<T> _next) { next = _next; }
    T getVal() { return val; }
    Node<T> * getNext()const { return next; }
};

template <class T>
class List
{
private:
    Node<T> * top;
public:
    List(T val) : top(new Node<T>(val, NULL)) {}
    List(const List& l) = delete;
    virtual ~List() { delete top; }
    Node<T> * getTop()const { return top; }
    void push(T val);
    Node<T> * pop();
    template <class U>
    friend ostream& operator<<(ostream & os, const List<T>& list);
};

template <class T>
void List<T>::push(T val)
{
    Node<T> * tmp = new Node<T>(val, top);
    //tmp->next = top;
    //tmp->getNext() = top;
    top = tmp;
}

template <class T>
Node<T> * List<T>::pop()
{
        if(top == NULL) throw Exception("List is empty!");
        Node<T> * node = top;
        top = top->getNext();
        return node;
}

template <class T>
ostream& operator<<(ostream& os, const List<T>& list)
{
    Node<T> * curr = list.getTop();
    while(curr != NULL)
    {
        os << curr->getVal() << " ";
        curr = curr->getNext();
    }
    return os;
}

#endif // LIST_H_INCLUDED
