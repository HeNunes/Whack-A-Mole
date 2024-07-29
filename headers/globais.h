#pragma once

#include <map>
#include <mutex>

using namespace std;

#define INDICE_JOGADOR 4 // Indice que representa o jogador no tabuleiro

const int NUM_TOUPEIRAS = 3;
const int TAMANHO_TABULEIRO = 3;
const int TEMPO_LIMITE_SEGUNDOS = 20;
extern int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

// Mapeia o input do usuário para um par (i, j) no tabuleiro
extern map<char, pair<int, int>> mapa;

extern mutex MutexTabuleiro; // Sincroniza o acesso ao tabuleiro
extern mutex MutexToupeira;  // Sincroniza a execução da thread do jogador e a thread das toupeiras para evitar bugs
extern bool movendo_toupeira;

