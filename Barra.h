#ifndef BARRA_H
#define BARRA_H
#include "No.h"


class No;

class Barra{
private:    
    No* noA;                                       
    No* noB;          
    double angulo;
    int id;
public:
    Barra(No* noA, No* noB, int id); // Construtor da Barra
    ~Barra(); // Destrutor da Barra
    No* getNoA();
    No* getNoB();
    double getAngulo();
    int getId();
};

#endif // BARRA_H