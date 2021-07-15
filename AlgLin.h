#ifndef ALGLIN_H
#define ALGLIN_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <iostream>
using namespace std;

double determinante(double** matriz, int dim); // Calcula o determinante de uma matriz
vector<double>* cramer(double** incognitas, double* resultados, int num); // Aplica a regra de cramer
double** LinearmenteIndependente(double** equacoes, int quantEquacoes, int quantIncognita, int* control_i, int* control_j); // Extrai uma matriz LI do conjunto de dados
double* findRespostas(double* respostas, int qNos, int* control_i, int* control_j); // Extrai as respostas para a matriz LI

double determinante(double** matriz, int dim){
    double det = 0;
    if (dim == 1){
        det = matriz[0][0];
        return det;
    } else if (dim == 2){
        det = (matriz[0][0] * matriz[1][1]) - (matriz[0][1] * matriz[1][0]);
        return det;
    } else {
        double** temp;
        temp = new double*[dim];
        for (int p = 0; p < dim; p++){
            temp[p] = new double[dim];
        }
        for (int p = 0; p < dim; p++){
            int h = 0, k = 0;
            for (int i = 1; i < dim; i++){
                for (int j = 0; j < dim; j++){
                    if (j == p){
                        continue;
                    }
                    temp[h][k] = matriz[i][j];
                    k++;
                    if (k == dim - 1){
                        h++;
                        k = 0;
                    }
                }
            }
            det = det + matriz[0][p] * pow(-1, p) * determinante(temp, dim - 1);
        }
        return det;
    }
}

vector<double>* cramer(double** incognitas, double* resultados, int num){
    double mainDet = determinante(incognitas, num);
    vector<double>* respostas = new vector<double>;
    if (mainDet != 0){
        for (int c = 0; c < num; c++){

            double** matrIncognita = new double*[num];
            for (int i = 0; i < num; i++){
                matrIncognita[i] = new double[num];
            }

            for (int i = 0; i < num; i++){
                for (int j = 0; j < num; j++){
                    if (j != c){
                        matrIncognita[i][j] = incognitas[i][j];
                    }
                    else {
                        matrIncognita[i][j] = resultados[i];
                    }
                }
            }

            double detIncognita = determinante(matrIncognita, num);
            double valor = detIncognita / mainDet;
            respostas->push_back(valor);
        }
    }
    return respostas;
}


double** LinearmenteIndependente(double** equacoes, int quantEquacoes, int quantIncognita, int* control_i, int* control_j){
    if (quantEquacoes == quantIncognita) return equacoes;
    int* seletor;
    seletor = new int[quantIncognita];
    for (int k = 0; k < quantIncognita; k++){
        if (k == quantIncognita - 1){
            seletor[k] = k + *control_i + *control_j;
        }
        else{
            seletor[k] = k + *control_i;
        }
    }
    double** LI;
    LI = new double*[quantIncognita];
    for (int i = 0; i < quantIncognita; i++){
        LI[quantIncognita] = new double[quantIncognita];
    }
    for (int i = 0; i < quantIncognita; i++){
        LI[i] = equacoes[seletor[i]];
    }
    if (determinante(LI, quantIncognita) == 0){
        (*control_j)++;
        if (*control_j == quantIncognita){
            (*control_j) = 0;
            (*control_i)++;
        }
        if (*control_i >= quantIncognita){
            throw new logic_error("Matriz quadrada LI Inexistente");
        }
        return LinearmenteIndependente(equacoes, quantEquacoes, quantIncognita, control_i, control_j);
    }
    return LI;   
}

double* findRespostas(double* respostas, int qNos, int* control_i, int* control_j){
    double* respostasNovas;
    respostasNovas = new double[qNos];
    int* seletor;
    seletor = new int[qNos];
    for (int k = 0; k < qNos; k++){
        if (k == qNos - 1)
            seletor[k] = k + *control_i + *control_j;
        else
            seletor[k] = k + *control_i;
    }
    for (int i = 0; i < qNos; i++){
        respostasNovas[i] = respostas[seletor[i]];
    }
    return respostasNovas;
}

#endif // ALGLIN_H