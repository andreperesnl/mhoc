/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newmain.cpp
 * Author: andre.ramos
 *
 * Created on 21 de Setembro de 2017, 11:06
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "math.h"



using namespace std;

/*
 * 
 */

int **mat_distancia;
vector<vector<int >> m_distancia;

class Vertice {
public:
    int id, x, y, capacidade, demanda;
    void set_values(int, int, int, int);
};

class Solucao {
public:
    std::vector<Vertice> medianas;
    std::vector<bool> mapa_medianas;
    std::vector<long> capacidade;
    vector<int> designacoes;
    bool aceitavel = false;

    void imprimir_dados() {
        std::cout << "Medianas:" << medianas.size() << " Mediana[0].id:" << medianas[0].id;
    }

    void inicializar(vector<Vertice> vertices) {
        std::cout << "Inicializando.\n";
        for(auto m:medianas){
            cout << "\nMediana: " << m.id << "\n";
        }
        mapa_medianas.assign(vertices.size(), false);
        capacidade.assign(medianas.size(), 0);
        designacoes.assign(vertices.size(), 0);

        for (int i = 0; i < vertices.size(); i++) {
            mapa_medianas[i] = false;
        }

        for (int i = 0; i < medianas.size(); i++) {
            mapa_medianas[medianas[i].id] = true;
            capacidade[i] = medianas[i].capacidade;
        }
        for (auto v : vertices) {
            int i_melhor = -1;
            long melhor_d = 999999999;
            for (int i = 0; i < medianas.size(); i++) {
                //                cout << "distância[" << i << "," << v.id << "]: " << mat_distancia[i][v.id] << "\n";
                if (capacidade[i] >= v.demanda && (m_distancia[medianas[i].id][v.id] < melhor_d)) {
                    i_melhor = i;
                    melhor_d = m_distancia[medianas[i].id][v.id];
                }
            }
            if (i_melhor > -1) {
                capacidade[i_melhor] -= v.demanda;
                designacoes[v.id] = i_melhor;
                                std::cout << "Associando " << v.id << " a " << medianas[i_melhor].id << "Capacidade Residual " << capacidade[i_melhor] << " Distancia: " << m_distancia[medianas[i_melhor].id][v.id] << "\n";
            } else {
                std::cout << "ENCONTRADA SOLUCAO INEFICIENTE!";
            }
        }

    }
};


const int SOLUCOES_INICIAIS = 5;
std::vector<Vertice> vertices;
std::vector<Solucao> solucoes;
int total_vertices;
int total_medianas;

void inicializar() {
    std::ifstream fin("c:\\temp\\SJC1.dat");
    std::string linha;

    std::getline(fin, linha);
    std::istringstream is(linha);
    is >> total_vertices >> total_medianas;

    std::cout << "Número de Vértices:" << total_vertices << "\nNúmero de medianas:" << total_medianas;

    int id = 0;
    for (std::string l; std::getline(fin, l);) {
        std::istringstream is2(l);
        Vertice tmp;
        is2 >> tmp.x >> tmp.y >> tmp.capacidade >> tmp.demanda;
        tmp.id = id;
        //                std::cout << "\nx:" << tmp.x << "\ny:" << tmp.y << "\ncap:" << tmp.cap << "\ndem:" << tmp.dem;
        vertices.push_back(tmp);
        id++;
    }

    std::cout << "\nTotal de " << vertices.size() << " vértices carregados!";
    std::cout << "\nV3:" << vertices[3].x;
}

void generateSetOfNumbers(int numbers[], int quantidade, int tamanho) {
    int tempNum; // temp variable to hold random number
    bool found; // used for value in array
    //    time_t timev;
    //    srand((unsigned) time(&timev));


    numbers[0] = rand() % 100; // generate the first number in the array
    //    time_t timev;
    //    std::cout << "Time in Milliseconds =" << time(&timev);
    //    std::cout << "\nRAND:" << (unsigned) rand();

    for (int index = 1; index < quantidade; index++) // loop to place other numbers 
    {
        do {
            tempNum = rand() % 100;
            found = false;

            for (int index2 = 0; index2 < quantidade; index2++)
                if (tempNum == numbers[index2]) {
                    found = true;
                    tempNum = numbers[index];
                }
        } while (found != false);
        numbers[index] = tempNum;
    }
}

Solucao gerar_solucao(int quantidade, int limite) {

    int valores[quantidade];

    generateSetOfNumbers(valores, quantidade, limite);
    vector<Vertice> m;
    cout << "\n[\n";
    for (int i = 0; i < quantidade; i++) {
        m.push_back(vertices[valores[i]]);
        cout << valores[i] << "\n";
    }
    cout << "]\n";
    Solucao solucao;
    solucao.medianas = m;
    solucao.inicializar(vertices);
    return solucao;


    //    
    //    cout << "solução\n";
    //    cout << winningNums[0] << " " << winningNums[1] << " "
    //            << winningNums[2] << " " << winningNums[3] << " "
    //            << winningNums[4] << endl;
}

int distancia(Vertice v1, Vertice v2) {
    return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) + ((v2.y - v1.y) * (v2.y - v1.y)));
}

void calculaFitness(Solucao s) {
    long total = 0;
    for (int i = 0; i < total_vertices; i++) {
        total += m_distancia[i][s.designacoes[i]];
    }

    cout << "\nTotal Distancia da solução:" << total << "\n";

}

int main() {
    inicializar();

    time_t timev;
    srand((unsigned) time(&timev));

    for (int i = 0; i < 5000; i++) {
        rand();
    }



    //
    mat_distancia = new int*[total_vertices];


    m_distancia.resize(total_vertices * total_vertices);

    for (int i = 0; i < total_vertices; i++)
        m_distancia[i].resize(total_vertices);


    for (int i = 0; i < total_vertices; i++) {
        //        mat_distancia[i] = new int[total_vertices];
        //        m_distancia.push_back(std::fill(0,total_vertices));
        ///std::fill(ivec.begin(), ivec.end(), i++);
    }


    for (int i = 0; i < total_vertices; i++) {
        for (int j = 0; j < total_vertices; j++) {
            //            mat_distancia[i][j] = distancia(vertices[i], vertices[j]);
            m_distancia[i][j] = distancia(vertices[i], vertices[j]);
            cout << "\ndistancia[" << i << "][" << j << "]:" << m_distancia[i][j];
        }
    }




    for (int i = 0; i < SOLUCOES_INICIAIS; i++) {
        Solucao s = gerar_solucao(total_medianas, total_vertices);
        solucoes.push_back(s);
        calculaFitness(s);
    }

    for (auto s : solucoes) {
        s.imprimir_dados();
    }
    //    std::cout << "\nDISTANCIA2:" << mat_distancia[0][1] << "\n";
    //    cout << "\ncoordenadas 99:" << vertices[99].x << "," << vertices[99].y;
    //    cout << "\ncoordenadas 7:" << vertices[7].x << "," << vertices[7].y;
    //    cout << "\nDistancia(Matriz) 99 e 7:" << m_distancia[99][7];
    //    cout << "\nDistancia(Dinâmico) 99 e 7:" << distancia(vertices[99], vertices[7]);
    //    cout << "\nTotal de Vertices:" << total_vertices;
    return 0;
}

