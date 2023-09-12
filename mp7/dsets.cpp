/* Your code here! */
#include "dsets.h"
#include <vector>

using std::vector;

void DisjointSets::addelements(int num) {
    //assume n elements are added from 0 to n-1
    if (num <= 0) {
        return;
    }
    for (int i = 0; i < num; i++) {
        set.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (set[elem] < 0) { //root case
        return elem;
    } else {
        return set[elem] = find(set[elem]); //path compression
    }
}

void DisjointSets::setunion(int a, int b) {
    //find roots
    int root1 = find(a);
    int root2 = find(b);
    //set new height
    int newSize = set[root1] + set[root2];
    //combine
    if (set[root1] <= set[root2]) {
        set[root2] = root1;
        set[root1] = newSize;
    } else {
        set[root1] = root2;
        set[root2] = newSize;
    }
}

int DisjointSets::size(int elem) {
    return -set[find(elem)];
}