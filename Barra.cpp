#include "Barra.h"
#include "No.h"
#include <iostream>
#include <cmath>

using namespace std;


Barra::Barra(No* noA, No* noB, int id){
    if (noA->getX() <= noB->getX()){
        this->noA = noA;
        this->noB = noB;
    }
    else {
        this->noA = noB;
        this->noB = noA;
    }
    this->id = id;

    angulo = atan((noA->getY() - noB->getY()) / (noA->getX() - noB->getX()));
}

Barra::~Barra(){
}

No* Barra::getNoA(){
    return this->noA;
}

No* Barra::getNoB(){
    return this->noB;
}

double Barra::getAngulo(){
    return this->angulo;
}

int Barra::getId(){
    return this->id;
}