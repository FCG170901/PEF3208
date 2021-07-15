#include <iostream>
#include <cmath>
#include <conio.h>
#include <fstream>
#include "Trelica.h"
#include "Forca.h"

#define PI 3.14159265

using namespace std;

int main(){
    bool repetidor = true;
    while (repetidor){
        bool rodando = true;
        int idNo = 0;
        int idConex = 0;
        vector<double>* reacoes = new vector<double>;
        Trelica* T = new Trelica();
        ofstream savedata;
        savedata.open("Ultima Trelica.txt");
        savedata << "[Dados salvos da ultima trelica criada]" << endl << endl;
        savedata << "Codigo da trelica (copiar e colar ela no programa para recriar): ";
        cout << "[PEF3208 - 2021] calculadora de treli" << (char) 135 << "as em C++" << endl << endl;
        cout << "-= Integrantes do grupo =-" << endl;
        cout << "Felipe Cesar Cuellar da Silva" << endl;
        cout << "Mariluce Pereira de Jesus" << endl;
        cout << "Maria Monique de Menezes Cavalcanti" << endl;
        cout << "Nelson Eug" << (char) 136 << "nio da Silveira Neto" << endl;
        cout << "Rodolfo Henrique Rom" << (char) 198 << "o da Silva" << endl << endl;
        cout << "Nota: Os c" << (char) 160 << "lculos ser" << (char) 198 << "o salvos no arquivo 'Ultima Trelica.txt', na mesma pasta deste execut" << (char) 160 << "vel." << endl << endl;
        cout << "1) Inserir novo n" << (char) 162 << endl;
        cout << "2) Conectar n" << (char) 162 << "s com uma barra" << endl;
        cout << "3) Inserir nova for" << (char) 135 << "a no sistema" << endl;
        cout << "4) Calcular" << endl;
        cout << "5) Resetar treli" << (char) 135 << "a (apagar for" << (char) 135 << "as, n" << (char) 162 << "s e barras)" << endl;
        cout << "0) Sair" << endl << endl;
        while(rodando){
            int op;
            cout << "Modo: ";
            cin >> op;

            while (cin.fail() || op < 0 || op > 5){
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> op;
            }

            switch (op){
                case 5:
                    cout << "Aviso: Apagar a treli" << (char) 135 << "a far" << (char) 160 << " com que o arquivo de salvamento seja limpo. Se desejar, copie-o antes de prosseguir." << endl;
                    cout << "Aperte qualquer tecla para confirmar o delete." << endl;
                    getch();
                    rodando = false;
                    system("clear||cls");
                    continue;
                case 4:
                    if (T->isostatica()){
                        savedata << endl << endl;
                        if (T->verificar()){
                            reacoes = T->calcular();
                            cout << "For" << (char) 135 << "as das barras (considere for" << (char) 135 << "as positivas como compress" << (char) 198 << "o e for" << (char) 135 << "as negativas como tra" << (char) 135 << (char) 198 << "o): " << endl;
                            savedata << "Forcas das barras (considere forcas positivas como compressao e forcas negativas como tracao): " << endl;
                            for (unsigned int i = 0; i < reacoes->size(); i++){
                                cout << "Fb(" << i << ") = " << reacoes->at(i) << endl;
                                savedata << "Fb(" << i << ") = " << reacoes->at(i) << endl;
                            }
                        cout << endl;
                        }
                        else{
                            cout << "Erro: A Treli" << (char) 135 << "a n" << (char) 198 << "o est" << (char) 160 << " em equil" << (char) 161 << "brio." << endl << endl;
                            savedata << "Erro: Sem equilibrio." << endl; 
                        }
                    }
                    else{
                        cout << "Erro: A Treli" << (char) 135 << "a n" << (char) 198 << "o " << (char) 130 << " isost" << (char) 160 << "tica." << endl << endl;
                        savedata << "Erro: Nao isostatico." << endl;
                    }
                    continue;
                case 3:
                    savedata << op << " ";
                    double angulo, modulo;
                    int no;
                    cout << "Insira o " << (char) 131 << "ngulo da for" << (char) 135 << "a: ";
                    cin >> angulo;

                    while (cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> angulo;
                    }

                    savedata << angulo << " ";
                    cout << "Insira o m" << (char) 162 << "dulo da for" << (char) 135 << "a: ";
                    cin >> modulo;

                    while (cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> modulo;
                    }

                    savedata << modulo << " ";
                    cout << "Insira o id do n" << (char) 162 << " onde a for" << (char) 135 << "a ser" << (char) 160 << " inserida: ";
                    cin >> no;

                    while (cin.fail() || no < 0 || no > T->getLastNo()->getId()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> no;
                    }      

                    savedata << no << " ";
                    angulo = angulo * (PI / 180);
                    T->addForca(angulo, modulo, no);
                    cout << "For" << (char) 135 << "a inserida no n" << (char) 162 << " " << no << "." << endl << endl;
                    continue;
                case 2:
                    int A, B;
                    cout << "Insira o id do n" << (char) 162 << " de origem: ";
                    cin >> A;

                    while (cin.fail() || A < 0 || A > T->getLastNo()->getId()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> A;
                    }  

                    cout << "Insira o id do n" << (char) 162 << " de destino: ";
                    cin >> B;

                    while (cin.fail() || B < 0 || B > T->getLastNo()->getId()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> B;
                    }  

                    if (T->conectar(idConex, A, B)){
                        idConex++;
                        savedata << op << " ";
                        savedata << A << " ";
                        savedata << B << " ";
                    }
                    continue;
                case 1:
                    double X, Y;
                    cout << "Valor da posi" << (char) 135 << (char) 198 << "o X do n" << (char) 162 << ": ";
                    cin >> X;

                    while (cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> X;
                    }  

                    cout << "Valor da posi" << (char) 135 << (char) 198 << "o Y do n" << (char) 162 << ": ";
                    cin >> Y;

                    while (cin.fail()){
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> X;
                    }

                    if (T->adicionar(idNo, X, Y)){
                        idNo++;
                        savedata << op << " ";
                        savedata << X << " ";
                        savedata << Y << " ";
                    }
                    continue;
                case 0:
                    rodando = false;
                    repetidor = false;
            }
        }
        savedata.close();
        delete T;
        delete reacoes;
    }
    return 0;
}

