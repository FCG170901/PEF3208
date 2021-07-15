#include <iostream>
#include <cmath>
#include "Forca.h"


using namespace std;

Forca::Forca(double modulo, double angulo, int no, int id){
    this->modulo = modulo;
    this->angulo = angulo;
    this->endereco = no;
    this->id = id;

}

Forca::~Forca(){

}

double Forca::getAngulo(){
    return angulo;
}

double Forca::getModulo(){
    return modulo;
}