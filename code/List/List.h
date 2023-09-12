#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template <class T>
class List {

  public:
    List(); 
    ~List(); 
    // need copy constructor and assignment operator

    void insert(const T &t, unsigned index);
    const T& remove(unsigned index);
    const T& get(unsigned index) const;
    bool isEmpty() const;
    unsigned length() const;

    void printReverse() const;
    void printForward() const;

  private:
    struct ListNode {
      const T& data;
      ListNode * next;
      ListNode(const T& data) : data(data), next(nullptr) { };
    };

    ListNode *head;

    void print_(ListNode *cur) const {
      if(cur->next != nullptr)
        print_(cur->next);
      cout << cur->data << " ";
    }

    ListNode *& find_(unsigned index) const {
      ListNode *thru = head;
      for (unsigned i=0; i < index; i++) {
        thru = thru->next;
      }
      return thru->next;
    }

};

#include "List.cpp"

#endif
