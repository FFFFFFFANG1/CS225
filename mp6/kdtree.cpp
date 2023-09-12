/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

/** * Determine whether the first point is bigger than the second one in the given dimension. If they are 
 * equal, then check the point size. **/
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (curDim < 0 || curDim >= Dim) return false;
    if (first[curDim] == second[curDim]) return first < second; //compare point in a dim
    if (first[curDim] < second[curDim]) return true; //compare point size
    return false;
}

/** * Calculate the Eudilean distance between two points and compare in order to decide whether to replace the current point with the potential one. 
 * If the distances are same, then compare the point size **/
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curr_dis = 0;
    double pot_dis = 0;
    for (int i = 0; i < Dim; i ++){
      curr_dis += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
      pot_dis += (target[i] - potential[i])*(target[i] - potential[i]);
    }
    if (pot_dis == curr_dis) return potential < currentBest; //compare point size
    return pot_dis < curr_dis;
}


/** * Perform a quickselect algorithm that given a vector of points, 
 * return the middle large member under current dimension. The average complexity is O(n) for
 * each run **/
template <int Dim>
Point<Dim> KDTree<Dim>::quickselect(vector<Point<Dim>>& newPoints, int left, int right, int k, int curDim)
{
    //choosing the median to be the pivot
    if (left == right) return newPoints[left];
    int pivotIdx = (left + right) / 2; 
    pivotIdx = partition(newPoints, left, right, pivotIdx, curDim);
    if (k == pivotIdx) return newPoints[k]; //the middle element
    else if (k < pivotIdx) return quickselect(newPoints, left, pivotIdx - 1, k, curDim); //the kth element is in the left subvector
    else return quickselect(newPoints, pivotIdx + 1, right, k, curDim); //the kth element is in the right subvector
}

/** * Helper function for quickselect algorithm. The function aims to find the medium in a given vector. 
 * The time complexity is O(n). **/
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& newPoints, int left, int right, int pivotIdx, int curDim)
{
  Point<Dim> pivot = newPoints[pivotIdx];
  swap(newPoints[pivotIdx], newPoints[right]);
  int saveIdx = left; //a pointer
  for (int i = left; i < right; i ++){
    if (smallerDimVal(newPoints[i], pivot, curDim)){
      swap(newPoints[saveIdx], newPoints[i]);
      saveIdx ++;
    }
  }
  swap(newPoints[saveIdx], newPoints[right]);
  return saveIdx;
}

/** * This function swaps two given element using reference **/
template <int Dim>
void KDTree<Dim>::swap(Point<Dim>& a, Point<Dim>& b)
{
  Point<Dim> temp = a;
  a = b;
  b = temp;
}

/** * The function is used to generate a vector sorted using quickselect for building up the KD tree. 
 * Here we pass by reference to modify**/
template <int Dim>
void KDTree<Dim>::KD_Vec(vector<Point<Dim>>& newPoints, vector<Point<Dim>>& KD_sorted ,int left, int right, int curDim)
{
  if (left > right) return;
  int mid = (left + right) / 2;
  Point<Dim> median = quickselect(newPoints, left, right, mid, curDim);
  KD_sorted[mid] = median; //the mid point of each subvector is the subroot
  KD_Vec(newPoints, KD_sorted, left, mid - 1, (curDim + 1) % Dim);
  KD_Vec(newPoints, KD_sorted, mid + 1, right, (curDim + 1) % Dim);
}

/** * This function use the sorted KD vector to generate the KD tree and return the root pointer. **/
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::build_KD(vector<Point<Dim>>& KD_sorted, int left, int right)
{
  if (left > right) return NULL;
  int mid = (left + right) / 2;
  KDTreeNode* root = new KDTreeNode(KD_sorted[mid]);
  root->left = build_KD(KD_sorted, left, mid - 1); //build left subtree
  root->right = build_KD(KD_sorted, mid + 1, right); //build right subtree
  return root;
}

/** *Constructor of KD tree. The function first copy the given list of points, sorts the copied list using quickselect. Then, the function calls 
 * build_KD to generate the entire KD tree.**/
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()){
      root = NULL;
      return;
    }
    vector<Point<Dim>> point_list = newPoints; //to modify the point_list, which is a const vector
    vector<Point<Dim>> KD_sorted(newPoints.size());
    KD_Vec(point_list, KD_sorted, 0, newPoints.size() - 1, 0);
    //build up the tree
    root = build_KD(KD_sorted, 0, newPoints.size() - 1);
}

/** * Copy constructor for KD tree. The function first flatten the given KD tree using in-order traversal to get a sorted KD vec. Then it calls build_KD
 * based on this vector. **/
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) 
{
  /**
   * @todo Implement this function!
   */
  vector<Point<Dim>> KD_sorted;
  in_order_push(other.root, KD_sorted);
  root = build_KD(KD_sorted, 0, KD_sorted.size() - 1);
}

/** * This helper function is used to flatten the given KD tree using in-order traversal. **/
template <int Dim>
void KDTree<Dim>::in_order_push(KDTreeNode* root, vector<Point<Dim>>& KD_sorted)
{
  if (root == NULL) return;
  in_order_push(root->left, KD_sorted);
  KD_sorted.push_back(root->point);
  in_order_push(root->right, KD_sorted);
}

/** * Overloading operator =. The function first deletes the current KD tree, if there is one. Then it follows the logic in the copy constructor
 * to generate a new KD tree based on the given one. **/
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) 
{
  /**
   * @todo Implement this function!
   */
  clear(root);
  vector<Point<Dim>> KD_sorted;
  in_order_push(rhs.root, KD_sorted);
  root = build_KD(KD_sorted, 0, KD_sorted.size() - 1);
  return *this;
}

/** * Destructor for KD tree. The function calls clear to delete the entire KD tree. **/
template <int Dim>
KDTree<Dim>::~KDTree() 
{
  /**
   * @todo Implement this function!
   */
  clear(root);
}

/** * This helper function is used to delete the entire KD tree recursively. **/
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* root)
{
  if (root == NULL) return;
  clear(root->left);
  clear(root->right);
  delete root;
}

/** * This function is used to find the nearest neighbor of the given query point. The function first calls findNearestNeighbor to find the nearest
 * neighbor of the given query point. Then it returns the nearest neighbor. **/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> cur_best = root->point;
    findNearestNeighbor(query, cur_best, root, 0);
    return cur_best;
}

/** * This helper function is used to find the nearest neighbor of the given query point. The function first checks if the current node is better
 * than the current best. If so, it updates the current best. Then it checks if the other side of the current node needs to be checked(by computing the radius). 
 * If so, it calls findNearestNeighbor recursively to check the other side. The time complexity is O(logn) **/
template <int Dim>
void KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query, Point<Dim>& cur_best, KDTreeNode* subroot, int curDim) const
{
  if (subroot == NULL) return;
  //depth first search
  KDTreeNode* next;
  KDTreeNode* other;
  if (smallerDimVal(query, subroot->point, curDim)){
    other = subroot->right;
    findNearestNeighbor(query, cur_best, subroot->left, (curDim + 1) % Dim);
  }else{
    other = subroot->left;
    findNearestNeighbor(query, cur_best, subroot->right, (curDim + 1) % Dim);
  }
  //check if the current node is better than the current best
  if (shouldReplace(query, cur_best, subroot->point)){
    cur_best = subroot->point;
  }
  
  //check the other side
  double r = 0.;
  double dist = 0.;
  for (int i = 0; i < Dim; i++){
    r += (query[i] - cur_best[i])*(query[i] - cur_best[i]);
  }
  dist = (query[curDim] - subroot->point[curDim])*(query[curDim] - subroot->point[curDim]);
  if (dist <= r){
    findNearestNeighbor(query, cur_best, other, (curDim + 1) % Dim);
  }
}