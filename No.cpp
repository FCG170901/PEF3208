#include "No.h"
#include "Forca.h"
#include "Barra.h"
#include <vector>
#include <iostream>

using namespace std;

No::No(int id, double posX, double posY){
    this->id = id;
    fid = 0;
    this->posX = posX;
    this->posY = posY;
    forcas = new vector<Forca*>;
    barras = new vector<int>;
}

No::~No(){
    for (unsigned int i = 0; i < forcas->size(); i++){
        delete forcas->at(i);
    }
    delete forcas;
    delete barras;
}

void No::addForca(double angulo, double modulo){
    Forca* nova = new Forca('n', modulo, angulo, id, fid);
    forcas->push_back(nova);
    fid++;
}

void No::addBarra(int id){
    barras->push_back(id);
}

double No::getX(){
    return posX;
}

double No::getY(){
    return posY;
}

int No::getId(){
    return id;
}

vector<Forca*>* No::getForcas(){
    return forcas;
}

vector<int>* No::getBarras(){
    return barras;
}