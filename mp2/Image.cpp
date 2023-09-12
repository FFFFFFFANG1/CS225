#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace cs225;

Image::Image(): PNG(){
}

Image::Image(unsigned a, unsigned b):PNG(a,b){
}

Image::Image(const Image &other): PNG(other){
}

Image::~Image(){
}

const Image & Image::operator= (const Image &other){
    PNG::operator=(other);
    return *this;
}

void Image::lighten()
{
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->l += 0.1;
            if (this->getPixel(i, j)->l > 1) this->getPixel(i, j)->l = 1;
        }
    }
}

void Image::lighten(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->l += amount;
            if (this->getPixel(i, j)->l > 1) this->getPixel(i, j)->l = 1;
        }
    }
}

void Image::darken(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->l -= 0.1;
            if (this->getPixel(i, j)->l < 0) this->getPixel(i, j)->l = 0;
        }
    }
}

void Image::darken(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->l -= amount;
            if (this->getPixel(i, j)->l < 0) this->getPixel(i, j)->l = 0;
        }
    }
}

void Image::saturate(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->s += 0.1;
            if (this->getPixel(i, j)-> s > 1) this->getPixel(i, j)->s = 1;
        }
    }
}

void Image::saturate(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->s += amount;
            if (this->getPixel(i, j)-> s > 1) this->getPixel(i, j)->s = 1;
        }
    }
}

void Image::desaturate(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->s -= 0.1;
            if (this->getPixel(i, j)-> s < 0) this->getPixel(i, j)->s = 0;
        }
    }
}

void Image::desaturate(double amount){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->s -= amount;
            if (this->getPixel(i, j)-> s < 0) this->getPixel(i, j)->s = 0;
        }
    }
}

void Image::grayscale(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->s = 0;
        }
    }
}

void Image::rotateColor(double degrees){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            this->getPixel(i, j)->h += degrees;
            if (this->getPixel(i, j)->h > 360){
                while (this->getPixel(i, j)->h > 0){
                    this->getPixel(i, j)->h -= 360;
                }
            }
            if (this->getPixel(i, j)->h < 0) {
                while (this->getPixel(i, j)->h < 0){
                    this->getPixel(i, j)->h += 360;
                }
            }
        }
    }
}

void Image::illinify(){
    for (unsigned int i = 0; i < this->width(); i++){
        for (unsigned int j = 0; j < this->height(); j++){
            if (this->getPixel(i, j)->h >= 113.5 && this->getPixel(i, j)->h < 293.5){
                this->getPixel(i, j)->h = 216;
            }else{
                this->getPixel(i, j)->h = 11;
            }
        }
    }
}

void Image::scale(double factor) {
    Image* newimag = new Image(*this);
    this->resize(this->width()*factor, this->height()*factor);
    for (unsigned i = 0; i < this->width(); i++) {
        for (unsigned j = 0; j < this->height(); j++) {
            unsigned oriw = min((unsigned)(i/factor), newimag->width() - 1);
            unsigned orih = min((unsigned)(j/factor), newimag->height() - 1);
            HSLAPixel *thisPixel = this->getPixel(i, j);
            HSLAPixel *newPixel = newimag->getPixel(oriw, orih);
            *thisPixel = *newPixel;
        }
    }
    delete newimag;
}

void Image::scale(unsigned w, unsigned h){
    double f_w = w * 1. / this->width();
    double f_h = h * 1. / this->height();
    if (f_w > f_h) this->scale(f_h);
    else this->scale(f_w);
}