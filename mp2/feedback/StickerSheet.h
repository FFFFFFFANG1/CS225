#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <iostream>

class StickerSheet{
    public:
        Image base_pic;

        Image** stic_arr;

        unsigned total;

        unsigned* X_;

        unsigned* Y_;

        unsigned used;

        StickerSheet();

        StickerSheet(const Image & picture, unsigned max);

        ~StickerSheet();
        
        StickerSheet(const StickerSheet & other);
        
        const StickerSheet & operator = (const StickerSheet & other);

        void changeMaxStickers(unsigned max);

        int addSticker(Image & sticker, unsigned x, unsigned y);

        bool translate(unsigned index, unsigned x, unsigned y);

        void removeSticker(unsigned index);

        Image* getStiker(unsigned index) const;
        
        Image render() const;
};




#endif