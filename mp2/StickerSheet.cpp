#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include "Image.h"
#include "iostream"

using namespace std;
using namespace cs225;

StickerSheet::StickerSheet(){
    base_pic = Image(1000,1000);
    for (unsigned i = 0; i < 1000; i++){
        for (unsigned j = 0; j < 1000; j++){
            base_pic.getPixel(i,j)->a = base_pic.getPixel(i,j)->h = base_pic.getPixel(i,j)->l = base_pic.getPixel(i,j)->s = 0;
        }
    }
    total = 1;
    used = 0;
    X_ = new unsigned[1];
    Y_ = new unsigned[1];
    stic_arr = new Image*[1];
    for (unsigned i = 0; i < 1; i ++){
        X_ [i] = Y_[i] = 0;
        stic_arr[i] = NULL;
    }
}

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    base_pic = picture;
    stic_arr = new Image*[max];
    total = max;
    used = 0;
    X_ = new unsigned[max];
    Y_ = new unsigned[max];
    for (unsigned i = 0; i < max; i ++){
        X_ [i] = Y_[i] = 0;
        stic_arr[i] = NULL;
    }
}

StickerSheet::~StickerSheet(){
    for (unsigned i = 0; i < total; i++){
        delete stic_arr[i];
    }
    delete[] stic_arr;
    delete[] X_;
    delete[] Y_;
}

StickerSheet::StickerSheet(const StickerSheet & other){
    stic_arr = NULL;
    base_pic = other.base_pic;
    total = other.total;
    used = other.used;
    stic_arr = new Image* [total];
    X_ = new unsigned[total];
    Y_ = new unsigned[total];
    for (unsigned i = 0; i < total; i ++){
        if (other.stic_arr[i] == NULL) stic_arr[i] = NULL;
        else stic_arr[i] = new Image(*other.stic_arr[i]);
        X_[i] = other.X_[i];
        Y_[i] = other.Y_[i];
    }
}

const StickerSheet& StickerSheet:: operator=(const StickerSheet& other){
    if (this == &other) return *this;
    delete [] stic_arr;
    delete[] X_;
    delete[] Y_;
    base_pic = other.base_pic;
    total = other.total;
    used = other.used;
    stic_arr = new Image* [total];
    X_ = new unsigned[total];
    Y_ = new unsigned[total];
    for (unsigned i = 0; i < total; i ++){
        if (other.stic_arr[i] == NULL) stic_arr[i] = NULL;
        else stic_arr[i] = new Image(*other.stic_arr[i]);
        X_[i] = other.X_[i];
        Y_[i] = other.Y_[i];
    }
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    Image** newtotal = new Image* [max];
    unsigned* newX_ = new unsigned[max];
    unsigned* newY_ = new unsigned[max];
    
    if (max <= total){
        for (unsigned i = 0; i < max; i ++){
            if (stic_arr[i] == NULL) newtotal[i] = NULL;
            else newtotal[i] = new Image(*stic_arr[i]);
            newX_[i] = X_[i];
            newY_[i] = Y_[i];
        }
        delete[] stic_arr;
        delete[] X_;
        delete[] Y_;
        stic_arr = newtotal;
        X_ = newX_;
        Y_ = newY_;
        total = max;
    }else{
        for (unsigned i = 0; i < total; i ++){
            if (stic_arr[i] == NULL) newtotal[i] = NULL;
            else newtotal[i] = new Image(*stic_arr[i]);
            newX_[i] = X_[i];
            newY_[i] = Y_[i];
        }
        for (unsigned j = total; j < max; j++){
            newtotal[j] = NULL;
            newX_[j] = 0;
            newY_[j] = 0;
        }
        delete[] stic_arr;
        delete[] X_;
        delete[] Y_;
        stic_arr = newtotal;
        X_ = newX_;
        Y_ = newY_;
        total = max;
    }
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{   
    int result = -1;
    for (unsigned i = 0; i < total; i ++){
        if (stic_arr[i] == NULL){
            stic_arr[i] = new Image(sticker);
            X_[i] = x;
            Y_[i] = y;
            used ++;
            result = i;
            break;
        }
    }
    return result;
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if (index >= total || stic_arr[index] == NULL) return false;
    // int judge = 1;
    // for (unsigned i = 0; i < used; i ++){
    //     for (unsigned j = 0; j < used; j ++){
    //         if (X_[i] == x && Y_[j] == y) judge = 0;
    //     }
    // }
    // if (judge == 1){
    X_[index] = x;
    Y_[index] = y;
        return true;
    // }
    // return false;
}

void StickerSheet::removeSticker(unsigned index){
    if (index >= total) return;
    delete stic_arr[index];
    stic_arr[index] = NULL;
    used--;
    return;
}

Image* StickerSheet::getSticker(unsigned index) const{
    if (index >= total) return NULL;
    return stic_arr[index];
}
    
Image StickerSheet::render() const{
    Image pic(base_pic);
    /*resize check*/
    for (unsigned k = 0; k < total; k ++){ 
        if (stic_arr[k] == NULL) continue;   
        if (stic_arr[k]->width() + X_[k] > pic.width()) pic.resize(X_[k] + stic_arr[k]->width(), pic.height());
        if (stic_arr[k]->height() + Y_[k] > pic.height()) pic.resize(pic.width(), Y_[k] + stic_arr[k]->height());
        // cout << "width" << base_pic.width() << "height" << base_pic.height() << endl;
    /*add stickers*/
        for (unsigned i = 0; i < stic_arr[k]->width(); i ++){
            for (unsigned j = 0; j < stic_arr[k]->height(); j++){
                //check alpha
                if (stic_arr[k]->getPixel(i, j)->a == 0) continue;
                *(pic.getPixel(i + X_[k], j + Y_[k])) = *(stic_arr[k]->getPixel(i, j));
            }
        }
    }
    return pic;
}