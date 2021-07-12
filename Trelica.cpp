#include "Trelica.h"
#include "AlgLin.h"
#include <cmath>
#include <vector>
#include <iostream>

#define PI 3.14159265

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

bool Trelica::isostatica(){
    if (forcas->size() + barras->size() == 2 * nos->size()) return true;
    else return false;
}

void Trelica::adicionar(int id, double X, double Y){
    No* novo = new No(id, X, Y);
    nos->push_back(novo);
    qNos++;
}

void Trelica::conectar(int id, int X, int Y){
    Barra* nova = new Barra(getNo(X), getNo(Y), id);
    getNo(X)->addBarra(id);
    getNo(Y)->addBarra(id);
    barras->push_back(nova);
    qBarras++;
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
        respostas[i] = 0;
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
    
    for (unsigned int i = 0; i < 2 * nos->size(); i++){ // Mapeando lado esquerdo da equação agora, para todos os nós
        for (int j = 0; j < qBarras; j++) sistema[i][j] = 0; // Pra não ter undefineds! (quase surtei ontem)
        for (unsigned int j = 0; j < nos->at(i/2)->getBarras()->size(); j++){ // <- Adicionar a informação das barras dentro do objeto Nó.

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
    double** matriz;
    double* respMatriz;
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