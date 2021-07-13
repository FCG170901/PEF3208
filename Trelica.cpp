#include "Trelica.h"
#include "AlgLin.h"
#include <cmath>
#include <vector>
#include <iostream>

#define PI 3.14159265

using namespace std;

Trelica::Trelica(){
    qNos = 0;
    qBarras = 0;
    nos = new vector<No*>;
    barras = new vector<Barra*>;
    forcas = new vector<vector<double>*>;
}

Trelica::~Trelica(){
    for (unsigned int i = 0; i < barras->size(); i++){
        delete barras->at(i);
    }
    delete barras;
    for (unsigned int i = 0; i < nos->size(); i++){
        delete nos->at(i);
    }
    delete nos;
    delete forcas;
}

No* Trelica::getNo(int id){
    for(unsigned int i = 0; i < nos->size(); i++){
        if (nos->at(i)->getId() == id){
            return nos->at(i);
        }
    }
    return NULL;
}

No* Trelica::getLastNo(){
    return nos->at(nos->size() - 1);
}

bool Trelica::isostatica(){
    if (forcas->size() + barras->size() == 2 * nos->size()) return true;
    else return false;
}

bool Trelica::adicionar(int id, double X, double Y){
    for (unsigned int i = 0; i < nos->size(); i++){
        if (X == nos->at(i)->getX() && Y == nos->at(i)->getY()){
            cout << "Erro: Esse n" << (char) 162 << " j" << (char) 160 << " existe." << endl << endl;
            return false;
        }
    }
    No* novo = new No(id, X, Y);
    nos->push_back(novo);
    cout << "N" << (char) 162 << " de id " << id << " inserido." << endl << endl;
    qNos++;
    return true;
}

bool Trelica::conectar(int id, int X, int Y){
    for (unsigned int i = 0; i < barras->size(); i++){
        int pontaA, pontaB;
        pontaA = barras->at(i)->getNoA()->getId();
        pontaB = barras->at(i)->getNoB()->getId();
        if ((pontaA == X && pontaB == Y) || (pontaA == Y && pontaB == X)){
            cout << "Erro: Essa barra j" << (char) 160 << " existe." << endl << endl;
            return false;
        }
        if (X == Y){
            cout << "Erro: Os n" << (char) 160 << "s alvo e destino s" << (char) 198 << "o iguais." << endl << endl;
            return false;
        }
    }
    Barra* nova = new Barra(getNo(X), getNo(Y), id);
    getNo(X)->addBarra(id);
    getNo(Y)->addBarra(id);
    barras->push_back(nova);
    cout << "Barra de id " << id << " inserida." << endl << endl;
    qBarras++;
    return true;
}

void Trelica::addForca(double angulo, double modulo, int no){
    nos->at(no)->addForca(angulo, modulo);
    vector<double>* forca = new vector<double>;
    forca->push_back(modulo);
    forca->push_back(angulo);
    forca->push_back(nos->at(no)->getX());
    forca->push_back(nos->at(no)->getY()); // Desnecessário?
    forcas->push_back(forca);
}

bool Trelica::verificar(){
    bool horiz = false;
    bool verti = false;
    bool mom = false;
    double somaH = 0.0;
    double somaV = 0.0;
    for (unsigned int i = 0; i < forcas->size(); i++){
        double trigonometricoH = cos(forcas->at(i)->at(1));
        if (trigonometricoH < -0.99) trigonometricoH = -1;
        if (trigonometricoH < 0.01 && trigonometricoH > -0.01) trigonometricoH = 0;
        if (trigonometricoH > 0.99) trigonometricoH = 1;

        double trigonometricoV = sin(forcas->at(i)->at(1));
        if (trigonometricoV < -0.99) trigonometricoV = -1;
        if (trigonometricoV < 0.01 && trigonometricoV > -0.01) trigonometricoV = 0;
        if (trigonometricoV > 0.99) trigonometricoV = 1;

        somaH = somaH + forcas->at(i)->at(0) * trigonometricoH;
        somaV = somaV + forcas->at(i)->at(0) * trigonometricoV;
    }
    if (somaH <= 0.01 && somaH >= -0.01){
        horiz = true;
    }
    if (somaV <= 0.01 && somaV >= -0.01){
        verti = true;
    }
    double leftpos[2];
    leftpos[0] = nos->at(0)->getX();
    leftpos[1] = nos->at(0)->getY();
    for (unsigned int i = 0; i < nos->size(); i++){ // Pegar o mais à esquerda
        if (nos->at(i)->getX() < leftpos[0]){
            leftpos[0] = nos->at(i)->getX();
            leftpos[1] = nos->at(i)->getY(); 
        }
    }
    double momento = 0.0;
    for (unsigned int i = 0; i < forcas->size(); i++){
        momento = momento + forcas->at(i)->at(2) * forcas->at(i)->at(0) * sin(forcas->at(i)->at(1));
    }
    if (momento <= 0.01 && momento >= -0.01){
        mom = true;
    }
    
    if (horiz && verti && mom) return true;
    return false;
}

vector<double>* Trelica::calcular(){ 
    
    // Declaração e inicialização
    double** sistema;
    double* respostas;
    sistema = new double*[qNos * 2];
    for (int i = 0; i < qNos * 2; i++){
        sistema[i] = new double[qNos];
    }
    respostas = new double[qNos * 2];

    for (unsigned int i = 0; i < 2 * nos->size(); i++){ // 2 equações para cada nó.
        respostas[i] = 0; // Inicializando com 0.

        for (unsigned int j = 0; j < nos->at(i / 2)->getForcas()->size(); j++){ // Forças de valores conhecidos (lado direito da equação).
            double trigonometrico;

            if (i % 2 == 0){
                trigonometrico = cos(nos->at(i / 2)->getForcas()->at(j)->getAngulo());
                if (trigonometrico < -0.99) trigonometrico = -1;
                if (trigonometrico < 0.01 && trigonometrico > -0.01) trigonometrico = 0;
                if (trigonometrico > 0.99) trigonometrico = 1;
            }

            else{
                trigonometrico = sin(nos->at(i / 2)->getForcas()->at(j)->getAngulo());
                if (trigonometrico < -0.99) trigonometrico = -1;
                if (trigonometrico < 0.01 && trigonometrico > -0.01) trigonometrico = 0;
                if (trigonometrico > 0.99) trigonometrico = 1;
            }

            respostas[i] = respostas[i] + trigonometrico * nos->at(i / 2)->getForcas()->at(j)->getModulo() * -1;
        }
    }
    
    for (unsigned int i = 0; i < 2 * nos->size(); i++){ // Mapeamento do lado esquerdo das equações

        for (int j = 0; j < qBarras; j++) sistema[i][j] = 0;

        for (unsigned int j = 0; j < nos->at(i/2)->getBarras()->size(); j++){

            int barraId = nos->at(i/2)->getBarras()->at(j); // ID de cada barra linkada no nó.
            Barra* reat = barras->at(barraId); // A barra com o ID.
            No* tipoA = reat->getNoA(); // nó do angulo normal da barra.

            double trigonometrico;
            if (i % 2 == 0){
                if (tipoA == nos->at(i/2)){
                    trigonometrico = cos(reat->getAngulo());
                    if (trigonometrico < -0.99) trigonometrico = -1;
                    if (trigonometrico < 0.01 && trigonometrico > -0.01) trigonometrico = 0;
                    if (trigonometrico > 0.99) trigonometrico = 1;
                    sistema[i][barraId] = trigonometrico;
                }
                else{
                    trigonometrico = cos(reat->getAngulo() + PI);
                    if (trigonometrico < -0.99) trigonometrico = -1;
                    if (trigonometrico < 0.01 && trigonometrico > -0.01) trigonometrico = 0;
                    if (trigonometrico > 0.99) trigonometrico = 1;
                    sistema[i][barraId] = trigonometrico;
                }
            }
            else{
                if (tipoA == nos->at(i/2)){
                    trigonometrico = sin(reat->getAngulo());
                    if (trigonometrico < -0.99) trigonometrico = -1;
                    if (trigonometrico < 0.01 && trigonometrico > -0.01) trigonometrico = 0;
                    if (trigonometrico > 0.99) trigonometrico = 1;
                    sistema[i][barraId] = trigonometrico;
                }
                else{
                    trigonometrico = sin(reat->getAngulo() + PI);
                    if (trigonometrico < -0.99) trigonometrico = -1;
                    if (trigonometrico < 0.01 && trigonometrico > -0.01) trigonometrico = 0;
                    if (trigonometrico > 0.99) trigonometrico = 1;
                    sistema[i][barraId] = trigonometrico;
                }
            }
        }
    }

    int storage_i = 0, storage_j = 0;
    double** matriz; // Matriz LI do sistema
    double* respMatriz; // Resposta das equações da matriz LI
    matriz = new double*[qNos];
    for (int i = 0; i < qNos; i++){
        matriz[i] = new double[qNos];
    }
    respMatriz = new double[qNos];
    matriz = LinearmenteIndependente(sistema, qNos * 2, qBarras, &storage_i, &storage_j);
    respMatriz = findRespostas(respostas, qBarras, &storage_i, &storage_j);

    vector<double>* valores = new vector<double>;
    valores = cramer(matriz, respMatriz, qBarras);
    return valores;
}