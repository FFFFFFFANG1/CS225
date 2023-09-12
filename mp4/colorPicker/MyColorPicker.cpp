#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <stdlib.h>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  //turn everything into green!
  double h = 92. + static_cast<double>(rand())/(static_cast<double> (RAND_MAX/(107. - 92.)));
  double s = 0.38 + static_cast<double>(rand())/(static_cast<double> (RAND_MAX/(1.0 - 0.38)));
  double l = 0.27 + static_cast<double>(rand())/(static_cast<double> (RAND_MAX/(0.82 - 0.27)));
  return HSLAPixel(h, s, l);
}
