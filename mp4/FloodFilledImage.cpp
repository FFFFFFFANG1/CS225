#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 * 
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) : png_(png){
  // pick_method = NULL;
  // trav_method = NULL;
}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 * 
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  pick_method.push_back(&colorPicker);
  trav_method.push_back(&traversal);
}

bool FloodFilledImage::is_end(ImageTraversal::Iterator it, ImageTraversal::Iterator end) const {
  if ((++it) != end) {
    return false;
  }
  return true;
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 * 
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 * 
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 * 
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */ 
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  /** @todo [Part 2] */
  unsigned count = 0;
  animation.addFrame(png_);//the initial frame
  for (unsigned i = 0; i < trav_method.size(); i++){
    for (ImageTraversal::Iterator it = trav_method[i]->begin(); it != trav_method[i]->end(); ++it) {

      HSLAPixel* apix = png_.getPixel((*it).x, (*it).y);
      HSLAPixel newpix = pick_method[i]->getColor((*it).x, (*it).y);
      *apix = newpix;
      count ++;

      if (count == frameInterval || is_end(it, trav_method[i]->end())) {
        animation.addFrame(png_);
        count = 0;
      }
    }
  }
  return animation;
}
