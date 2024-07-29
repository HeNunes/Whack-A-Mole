#ifndef JOGO_H
#define JOGO_H

#include <chrono>
#include <thread>
#include <vector>
#include "Toupeira.h"
#include "Jogador.h"

using namespace std;

// Classe do jogo
class WhackAMole 
{
    private:
        int pontuacao;
        chrono::time_point<chrono::steady_clock> tempo_inicio;
        vector<Toupeira> toupeiras;
        vector<thread> threadsToupeiras;

    public:
        WhackAMole(); 

        // Função principal de execução do jogo
        void iniciarJogo();

        // Le e trata a jogada do usuário em relação ao jogo, verificando o acerto ou erro
        void verifica_jogada(Jogador &jogador);

        // Calcula e retorna o tempo restante até o fim do jogo
        int tempoRestante();
};

#endif