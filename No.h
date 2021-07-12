#ifndef NO_H
#define NO_H

#include "Forca.h"
#include "Barra.h"
#include <vector>

using namespace std;

class Barra;

class No{
private:
    int id, fid; // Identificacao do No.
    double posX, posY; // Posicao no plano cartesiano.
    vector<Forca*>* forcas;
    vector<int>* barras;
public:
    No(int id, double posX, double posY);
    ~No();
    void addForca(double angulo, double modulo);
    void addBarra(int id);
    double getX();
    double getY();
    int getId();
    vector<Forca*>* getForcas();
    vector<int>* getBarras();
};

#endif // NO_H