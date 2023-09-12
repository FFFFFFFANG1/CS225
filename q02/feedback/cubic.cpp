#include <iostream>
#include "cubic.h"

using namespace std;

Cubic::Cubic(){
    Polynomial(3);
}

Cubic::Cubic(float a3, float a2, float a1, float a0){
    Polynomial* c = new Polynomial(3);
    c->setCoeff(0, a0);
    c->setCoeff(1, a1);
    c->setCoeff(2, a2);
    c->setCoeff(3, a3);
}

