#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

double ImageTraversal::get_diff(const HSLAPixel & p1, const HSLAPixel & p2) {
  return calculateDelta(p1, p2);
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  // it = path_.front();
}

ImageTraversal::Iterator::Iterator(std::vector<Point>::iterator it) {
  this->it = it;
}

// ImageTraversal::Iterator::Iterator(bool is_end){
  // if (is_end) it = path_.back();
  // else it = path_.front();
// }

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  ++it;
  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  return *it;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  return !(it == other.it);
}

Point ImageTraversal::Iterator::getcurr() const {
  return *it;
}
