#include <iostream>
#include "List.h"

// compile:  g++ -std=c++1y  mainList.cpp

int main() {

    List <char> *list = new List <char>;

    list->insert(*(new char('c')), 0);
    list->insert(*(new char('s')), 1);
    list->insert(*(new char('2')), 2);
    list->insert(*(new char('2')), 3);
    list->insert(*(new char('5')), 4);

    list->printReverse();

    cout << "Lenght: " << list->length() << endl;

    list->printForward();

    delete & list->remove(1);

    list->printForward();

    cout << "Lenght: " << list->length() << endl;

    delete list;

    return 0;
}

