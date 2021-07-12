#ifndef BARRA_H
#define BARRA_H
#include "No.h"

class No;

class Barra{                                        // Essa classe serve para representar uma Barra em si, conectada entre dois nós e que possui um esforço solicitante
private:    
    No* noA;                                       
    No* noB;          
    double angulo;
    double modulo;
    int id;
public:
    Barra(No* noA, No* noB, int id);      // A Barra recebe a informação necessária para "criar o objeto do seu esforço". Também recebe dois nós, que são suas conexões
    ~Barra();
    No* getNoA();
    No* getNoB();
    double getAngulo();
    int getId();
    void setModulo(double modulo);
    void imprimir();
};                                                  // Usando a lógica desse combo de Classes (Barra e Esforco), poderemos preencher o Cramer utilizando somente objetos Barra. Já que a Barra contém: 
                                                    //                                                                                                                          1) A informação dos Nós que ela está conectada e, portanto, a informação das forças de apoio que agem no nó (se existirem)
#endif                                              //                                                                                                                          2) A informação do esforço solicitante que queremos calcular
                                                    //                                                                                                                          Obs: A afirmação "1)" leva em consideração de que o Nó possua a informação das força de apoio. No momento em que essa observação está sendo escrita ela não tem