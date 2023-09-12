#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include <iostream>

using namespace cs225;
using namespace std;

int main() {
  Image base;
  Image alma;
  alma.readFromFile("tests/bg.png");


  Image i;
  i.readFromFile("tests/i.png");

  Image j;
  j.readFromFile("tests/emoji.png");

  // cout << j.width() <<j.height()<<endl;
  Image k;
  k.readFromFile("tests/qw.png");
  // cout << k.width() <<k.height()<<endl;

  Image h;
  h.readFromFile("tests/doge.png");
    // cout << h.width() <<h.height()<<endl;

  /*cons test*/
  StickerSheet sheet(alma, 5);
  // cout << "def cons" << endl;
  // cout << "total: " << sheet.total << "used: " << sheet.used << endl;
  
  StickerSheet* deltest=new StickerSheet(alma, 10);
  delete deltest;
  // cout << "del suc" << endl;

  StickerSheet cosheet(sheet);
  // cout << "copy suc" << endl;
  // cout << "total: " << cosheet.total << "used: " << cosheet.used << endl;
  
  cosheet.changeMaxStickers(10);
  sheet.changeMaxStickers(10);
  // cout << "change suc" << endl;
  // cout << "nowtotal: " << cosheet.total << "nowused: " << cosheet.used << endl;
  
  
sheet.addSticker(j, 50, 50);
sheet.addSticker(k, 75, 10);
sheet.addSticker(h, 10, 10);
sheet.addSticker(i, 100,100);

  sheet.translate(0, 10, 100);
  sheet.translate(1, 1000, 70);
  sheet.translate(2, 2000, 200);
  sheet.removeSticker(3);
  alma = sheet.render();
  alma.writeToFile("tests/myImage.png");
  return 0;
}