#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);
  
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;
  void traverse(const Point & this_point);
  vector<vector<int> > visited_;
  // vector<Point> path_;
  
private:
  ImageTraversal::Iterator iter;
  Point start_;
  double tolerance_;
  PNG png_;
  // stack<Point> stack_;
};

#endif
