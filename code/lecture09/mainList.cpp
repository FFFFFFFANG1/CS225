#include <iostream>
#include "List.h"

// compile:  g++ -std=c++1y  mainList.cpp

int main() {

    List <char> *list = new List <char>;

    list->insertAtFront(*(new char('s')));
    list->insertAtFront(*(new char('c')));

    list->printReverse();

    delete list;


    return 0;
}

