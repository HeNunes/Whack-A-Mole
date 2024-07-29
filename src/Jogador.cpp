#include <iostream>
#include <cstdlib>
#include <map>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <termios.h>
#include <thread>
#include <mutex>
#include <sys/ioctl.h>
#include "globais.h"
#include "Toupeira.h"
#include "Jogador.h"

using namespace std;

// Construtor
Jogador::Jogador()
{
    this->escolha = EOF;
    this->linha = -1;
    this->coluna = -1;
    this->pos_valida = false;
}

// Le a posição escolhida pelo jogador
void Jogador::input() 
{
    struct termios antigo, novo;
    char c;

    tcgetattr(STDIN_FILENO, &antigo);
    novo = antigo;
    novo.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &novo);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &antigo);

    escolha = c;
    
    auto it = mapa.find(toupper(c));

    // Calculando os atributos da classe com base na escolha realizada:
    if(it == mapa.end())
        pos_valida = false;
    else
        pos_valida = true;
    linha  = it->second.first;
    coluna = it->second.second;
}

void Jogador::ocupa_posicao_jogador()
{
    tabuleiro[linha][coluna] = INDICE_JOGADOR;
}

void Jogador::desocupa_posicao_jogador()
{
    tabuleiro[linha][coluna] = 0;
}

// Funções "get":

char Jogador::get_escolha() const {
    return escolha;
}
int Jogador::get_linha() const {
    return linha;
}
int Jogador::get_coluna() const {
    return coluna;
}
bool Jogador::posicao_valida() const {
    return pos_valida;
}
