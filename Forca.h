#ifndef FORCA_H
#define FORCA_H

class Forca{
private:
char tipo;
double modulo, angulo;
int endereco, id;

public:
    Forca(char tipo, double modulo, double angulo, int no, int id);
    ~Forca();
    double getAngulo();
    double getModulo();
    void imprimir();
};

#endif // FORCA_H