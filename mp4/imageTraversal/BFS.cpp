
#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) :
      start_(start), tolerance_(tolerance), png_(png) {  
  visited_.resize(png_.height(), vector<int>(png_.width(),0));
  for(unsigned i = 0; i < png_.width(); i ++){
    for (unsigned j = 0; j < png_.height(); j ++){
      visited_[j][i]= 0;
    }
  }
  // path_.push_back(start_);
  traverse(start_);
  //sentinal value
  // path_.push_back(Point(-1,-1));
}

void BFS::traverse(Point & this_point) {
    //push 
    Point up(this_point.x, this_point.y - 1);
    Point left(this_point.x - 1, this_point.y);
    Point down(this_point.x, this_point.y + 1);
    Point right(this_point.x + 1, this_point.y);
    add(right);
    add(down);
    add(left);
    add(up);

    path_.push_back(this_point);
    if (visited_[this_point.y][this_point.x] == 0){
        visited_[this_point.y][this_point.x] = 1;
    }
    //pop
    if (!empty()) { 
      Point next = pop();  
      traverse(next);
    }
//     //push 
//     add(this_point);
//     //pop
//     if (!empty()) { 
//         Point next = pop();  
//         if (visited_[next.y][next.x] == 0){
//             path_.push_back(next);
//             visited_[next.y][next.x] = 1;
//         }
//         traverse(next);
//     }
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
 ImageTraversal::Iterator begin_(path_.begin());
  // begin_.it = path_.begin();
  return begin_;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  ImageTraversal::Iterator end_(path_.end());
  // end_.it = path_.end();
  return end_;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  if ((point.x) < png_.width() && (point.y) < png_.height() &&
      visited_[point.y][point.x] == 0 && 
      tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x, point.y)))) {

        queue_.push(point);
        visited_[point.y][point.x] = 1;
  }
  // if ((point.y +1) < png_.height() &&   
  //     visited_[point.y +1][point.x] == 0 && 
  //     tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x, point.y +1)))) 
  //       queue_.push(Point(point.x, point.y +1));

  // if (point.x != 0 && 
  //     visited_[point.y][point.x -1] == 0 && 
  //     tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x -1, point.y)))) 
  //       queue_.push(Point(point.x -1, point.y));

  // if (point.y != 0 && 
  //     visited_[point.y -1][point.x] == 0 && 
  //     tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x, point.y -1)))) 
  //       queue_.push(Point(point.x, point.y -1));  
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  Point element = queue_.front();
  queue_.pop();
  return element;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  return iter.getcurr();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  return queue_.empty();
}
