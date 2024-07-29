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

using namespace std;

// Construtor
Toupeira::Toupeira(int i)
{
    this->linha  = -1;
    this->coluna = -1;
    this->id     = i;
}

void Toupeira::ocupa_posicao_toupeira()
{
    tabuleiro[linha][coluna] = id;
}
void Toupeira::desocupa_posicao_toupeira()
{
    // Caso a toupeira esteja em uma casa que nao foi ocupada pelo jogador
    if((linha != -1 && coluna != -1) && (tabuleiro[linha][coluna] != INDICE_JOGADOR))
        tabuleiro[linha][coluna] = 0;
}

// Escolhe uma nova posição desocupada do tabuleiro
void Toupeira::escolhe_posicao() 
{
    do
    {
        linha  = rand() % TAMANHO_TABULEIRO; 
        coluna = rand() % TAMANHO_TABULEIRO;
    } while(tabuleiro[linha][coluna] != 0);       
}

// Move a toupeira de uma casa para outra
void Toupeira::mover_toupeira()
{
    unique_lock<mutex> lock(MutexTabuleiro);
    desocupa_posicao_toupeira();
    escolhe_posicao();
    ocupa_posicao_toupeira();
    lock.unlock();
}

// Funções "get":

int Toupeira::get_id() const {
    return id;
}
int Toupeira::get_linha() const {
    return linha;
}
int Toupeira::get_coluna() const {
    return coluna;
}
