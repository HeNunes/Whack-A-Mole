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
#include "tela.h"
#include "Toupeira.h"
#include "Jogador.h"
#include "WhackAMole.h"

using namespace std;

// Construtor
WhackAMole::WhackAMole() : pontuacao(0) 
{
    // Inicializa o tabuleiro e o tempo de jogo
    for(int i = 0; i < TAMANHO_TABULEIRO; ++i) 
    {
        for(int j = 0; j < TAMANHO_TABULEIRO; ++j)
            tabuleiro[i][j] = 0;
    }
    srand(static_cast<unsigned>(time(0)));
}

// Função principal de execução do jogo
void WhackAMole::iniciarJogo() 
{
    // Exibe o tutorial
    print_tutorial();

    // Inicializando as variáveis:
    tempo_inicio = chrono::steady_clock::now();
    for(int i = 0; i < NUM_TOUPEIRAS; ++i)
        toupeiras.push_back(Toupeira(i + 1));

    for(int i = 0; i < NUM_TOUPEIRAS; ++i) 
    {
        // Gera-se uma thread para cada toupeira
        threadsToupeiras.push_back(thread([this, i]() 
        {
            while (tempoRestante() > 0) 
            {
                /*
                    Para sincronizar o jogo, as toupeiras devem impedir que a
                    jogada seja processada enquanto elas se movem por conta própria, ou seja,
                    sem a intervenção do jogador.
                    Para isso, a toupeira assume o mutex relativo ao seu movimento.
                */
                unique_lock<mutex> lock(MutexToupeira);
                movendo_toupeira = true; // A toupeira vai iniciar um movimento
                
                // Movendo a toupeira
                toupeiras[i].mover_toupeira();
                mostra_tabuleiro();

                movendo_toupeira = false; // A toupeira encerrou seu movimento
                lock.unlock();

                this_thread::sleep_for(chrono::seconds(i + 1));
            }
        }));
    }

    // Gera-se uma thread para o jogador (leitura e tratamento da stdin)
    thread jogadorThread([this]() 
    {
        Jogador jogador = Jogador();
        while (tempoRestante() > 0) 
        {
            // Caso o movimento da toupeira nao esteja sendo processado:
            // Le (e trata) o input do jogador
            if(!movendo_toupeira)
            {
                // Le a jogada
                jogador.input();
                verifica_jogada(jogador);
            }
        }
    });

    // Unindo as threads:
    for(auto &threadToupeira : threadsToupeiras) 
    {
        if(threadToupeira.joinable())
            threadToupeira.join();
    }
    jogadorThread.join();

    // Exibindo a pontuação final
    cout << endl << "Tempo esgotado! Fim do jogo." << endl;
    cout << "Voce acertou " << pontuacao << " toupeiras!" << endl;
}

// Le e trata a jogada do usuário em relação ao jogo, verificando o acerto ou erro
void WhackAMole::verifica_jogada(Jogador &jogador)
{       
    // Caso a posicao exista no tabuleiro
    if(jogador.posicao_valida())
    {
        /*
            Assume o mutex do tabuleiro para que o calculo da variavel "hit" 
            não seja comprometido, além de garantir a validade da posição ocupada
        */
        unique_lock<mutex> lock(MutexTabuleiro);
        
        int hit = tabuleiro[jogador.get_linha()][jogador.get_coluna()];
        jogador.ocupa_posicao_jogador();
        
        lock.unlock();

        // Caso o jogador tenha acertado a toupeira
        if(hit != 0) 
        {
            // Movendo a toupeira e atualizando a pontuação
            toupeiras[hit - 1].mover_toupeira();
            mostra_tabuleiro(); 
            pontuacao++;
        }
        lock.lock();
        jogador.desocupa_posicao_jogador();
        lock.unlock();
    }
}

// Calcula e retorna o tempo restante até o fim do jogo
int WhackAMole::tempoRestante() 
{
    auto agora   = chrono::steady_clock::now();
    auto duracao = chrono::duration_cast<chrono::seconds>(agora - tempo_inicio);
    return (TEMPO_LIMITE_SEGUNDOS - duracao.count());
}