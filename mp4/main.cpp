
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  
  
  PNG png;
  
  png.readFromFile("shet.png");
  FloodFilledImage image(png);
  BFS bfs1(png, Point(200, 200), 0.05);
  DFS dfs1(png, Point(200, 100), 0.05);
  DFS dfs2(png, Point(200, 400), 0.05);
  DFS dfs3(png, Point(200, 450), 0.05);
  DFS dfs4(png, Point(400, 400), 0.05);
  MyColorPicker My;
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill(dfs1, My);
  image.addFloodFill(bfs1, rainbow);
  image.addFloodFill(dfs2, My);
  image.addFloodFill(dfs4, My);
  image.addFloodFill(dfs3, rainbow);
  Animation animation = image.animate(10000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  
  return 0;
}
