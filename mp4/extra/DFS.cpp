#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) :
    start_(start), tolerance_(tolerance), png_(png) {
    visited_.resize(png_.height(), vector<int>(png_.width()));
    for(unsigned i = 0; i < png_.width(); i ++){
      for (unsigned j = 0; j < png_.height(); j ++){
        visited_[j][i]= 0;
      }
    }
    traverse(start_);
    //sentinal value
    // path_.push_back(Point(-1,-1));
}


void DFS::traverse(const Point & this_point) {
    // //push 
    // add(this_point);
    // path_.push_back(this_point);
    // visited_[this_point.x][this_point.y] = 1;
    // //pop
    // if (!deeper) { 
    //   pop();  
    //   traverse(stack_.top());
    // }
    if (this_point.x < png_.width() && this_point.y < png_.height() &&
        tolerance_ > get_diff(*(png_.getPixel(this_point.x, this_point.y)), *(png_.getPixel(start_.x, start_.y))) &&
        visited_[this_point.y][this_point.x] == 0){
          add(this_point);
          visited_[this_point.y][this_point.x] = 1;
        }else {return;}

    traverse(Point(this_point.x, this_point.y - 1));
    traverse(Point(this_point.x - 1, this_point.y));
    traverse(Point(this_point.x, this_point.y + 1));
    traverse(Point(this_point.x + 1, this_point.y));
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  ImageTraversal::Iterator begin_(path_.begin());
  // begin_.it = path_.begin();
  return begin_;
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  ImageTraversal::Iterator end_(path_.end());
  // end_.it = path_.end();
  return end_;
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  path_.push_back(point);
  // deeper = false;
  // if (point.y != 0 && 
  //     tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x, point.y -1))) && 
  //     visited_[point.y -1][point.x] == 0) {
  //       stack_.push(Point(point.x, point.y -1));
  //       deeper = true;
  //       return;
  //     }
  // if (point.x != 0 && 
  //   tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x -1, point.y))) && 
  //   visited_[point.y][point.x -1] == 0) {
  //     stack_.push(Point(point.x -1, point.y));
  //     deeper = true;
  //     return;
  //   }   
  // if ((point.y +1) < png_.height() && 
  //   tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x, point.y +1))) &&
  //   visited_[point.y +1][point.x] == 0){
  //     stack_.push(Point(point.x, point.y +1));
  //     deeper = true;
  //     return;
  //   } 
  // if ((point.x +1) < png_.width() && 
  //     tolerance_ > get_diff(*(png_.getPixel(start_.x, start_.y)), *(png_.getPixel(point.x +1, point.y))) && 
  //     visited_[point.y][point.x +1] == 0 ) {
  //       stack_.push(Point(point.x +1, point.y));
  //       deeper = true;
  //       return;
  //     }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  // Point element = stack_.top();
  // stack_.pop();
  Point element = path_.back();
  path_.pop_back();
  return element;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  return iter.getcurr();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  return path_.empty();
}
