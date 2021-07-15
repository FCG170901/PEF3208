#ifndef FORCA_H
#define FORCA_H


class Forca{
private:
double modulo, angulo;
int endereco, id;

public:
    Forca(double modulo, double angulo, int no, int id); // Construtor de Forca
    ~Forca(); // Destrutor de Forca
    double getAngulo();
    double getModulo();
};


#endif // FORCA_H