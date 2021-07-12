#ifndef TRELICA_H
#define TRELICA_H

#include <vector>
#include "No.h"
#include "Barra.h"

using namespace std;

class Trelica{
private:
    int qNos, qBarras;
    vector<No*>* nos;
    vector<Barra*>* barras;
    vector<vector<double>*>* forcas;
public:
    Trelica();
    ~Trelica();
    No* getNo(int id);
    bool isostatica();
    void adicionar(int id, double X, double Y); // Adiciona um Nó.
    void conectar(int id, int X, int Y); // Conecta dois Nós com uma Barra.
    void addForca(double angulo, double modulo, int no); // Adiciona a força no nó e no vector de verificação de equilíbrio.
    bool verificar(); // Verifica se barra está em equilíbrio para ser processada.

    vector<double>* calcular(); // Calcula todas as forças quando todas as informações já estão carregadas.
};

#endif // TRELICA_H