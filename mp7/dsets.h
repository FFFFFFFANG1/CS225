/* Your code here! */
#ifndef _DSETS_H_
#define _DSETS_H_
#include <vector>


using std::vector;

/* The disjoint sets class, the object of which will be used to represent
 * the disjoint sets of uprooted trees. */
class DisjointSets {
public:
    /**
     * The function creates n unconnected root nodes at the end of the vector.
     * @param num Number of nodes to be added.
     * @return none
     */
    void addelements(int num);
    /**
     * The function finds the root of the corresponding element in the 
     * up tree.
     * @param elem Point to be found.
     * @return root of the up tree.
     */
    int find(int elem);
    /**
     * The function combines two up trees.
     * @param a Tree a to be combined.
     * @param b Tree b to be combined.
     * @return none
     */
    void setunion(int a, int b);
    /**
     * The function returns the size of the up tree.
     * @param elem Point to be found.
     * @return size of the up tree.
     */
    int size(int elem);
private:
    /*The vector representing the disjoint set. Each element has
    the value of its root. If the element is root, then the value is
    the negative size*/
    vector<int> set;
};
#endif