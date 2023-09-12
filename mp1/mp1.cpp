#include <string>
#include "mp1.h"
#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    cs225::PNG input, output;
    int32_t checkin = input.readFromFile(inputFile);
    if (!checkin) return;
    output.resize(input.width(),input.height());
    HSLAPixel* inpix, * outpix;
    for (uint32_t i = 0; i < input.height(); i++){
        for (uint32_t j = 0; j < input.width(); j++){
            inpix = input.getPixel(j, i);
            outpix = output.getPixel(input.width()-1-j, input.height()-1-i);
            *outpix = *inpix;
        }
    }
    int32_t checkout = output.writeToFile(outputFile);
    if (!checkout) return;
}
