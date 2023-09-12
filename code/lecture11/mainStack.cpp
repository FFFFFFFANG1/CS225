#include <iostream>
#include "Stack.h"

// compile:  g++ -std=c++1y  mainStack.cpp

int main() {

    Stack <char> *stack = new Stack <char>;

    stack->push(*(new char('5')));
    stack->push(*(new char('2')));
    stack->push(*(new char('2')));
    stack->push(*(new char('s')));
    stack->push(*(new char('c')));

    stack->printStack();

    delete & stack->pop();
    delete & stack->pop();

    stack->printStack();

    delete & stack->pop();
    delete & stack->pop();
    delete & stack->pop();

    delete stack;


    return 0;
}

