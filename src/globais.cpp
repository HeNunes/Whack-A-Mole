#include <map>
#include <mutex>
#include "globais.h"

using namespace std;

int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

// Mapeia o input do usuário para um par (i, j) no tabuleiro
map<char, pair<int, int>> mapa = {{'Q', {0, 0}}, {'W', {0, 1}}, {'E', {0, 2}},
                                {'A', {1, 0}}, {'S', {1, 1}}, {'D', {1, 2}},
                                {'Z', {2, 0}}, {'X', {2, 1}}, {'C', {2, 2}}};

mutex MutexTabuleiro; // Sincroniza o acesso ao tabuleiro
mutex MutexToupeira;  // Sincroniza a execução da thread do jogador e a thread das toupeiras para evitar bugs
bool movendo_toupeira = false;