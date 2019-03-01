#include <iostream>
#include "outFunc.h"
#include "list.h"

int main()
{
    const char * a = "a";
    const char * b = "b";
    cout << sum(a, b) << endl;
    cout << sum("czy ", "dziala?\n");

    List<int> * list = new List<int>(42);
    list->pop();
    list->pop();
    list->push(50);
    list->push(12);
    list->push(63);
    cout << (*list) << endl;
    delete list;
    return 0;
}
