#include <iostream>
#include <cstdlib>
#include <ctime>
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

using namespace std;

// Funções auxiliares para obter as dimnesões do terminal
int LarguraTerminal()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col; // Retorna o número de colunas no terminal
}
int AlturaTerminal()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_row; // Retorna o número de colunas no terminal
}

// Renderiza o tabuleiro
void mostra_tabuleiro()
{
    unique_lock<mutex> lock(MutexTabuleiro);
    system("clear");

    int largura = LarguraTerminal();
    int altura  = AlturaTerminal();
    int espacosAntes = (largura - TAMANHO_TABULEIRO * 2) / 2;
    int linhasAntes  = (altura - TAMANHO_TABULEIRO * 2) / 2;

    for(int i = 0; i < linhasAntes; i++)
        cout << endl;

    for(int i = 0; i < TAMANHO_TABULEIRO; ++i) 
    {
        for (int k = 0; k < espacosAntes; ++k)
            cout << " ";

        for(int j = 0; j < TAMANHO_TABULEIRO; ++j)
        {
            if(tabuleiro[i][j] == INDICE_JOGADOR)
                cout << YELLOW << "|" << GREEN << "X" << YELLOW << "|" << RESET << "";
            else if(tabuleiro[i][j] > 0)
                cout << YELLOW << "|" << RED << "O" << YELLOW << "|" << RESET << "";
            else
                cout << YELLOW << "|" << YELLOW << "#" << YELLOW << "|" << RESET << "";
        }
        cout << endl;
    }
}

// Exibe um tutorial ao usuário
void print_tutorial()
{
    char c;

    cout << "Bem-vindo ao Whack-a-Mole!\n";
    cout << "Utilize o teclado para acertar as toupeiras!" << endl;
    cout << "As casas marcadas por " << YELLOW << "# " << RESET << "não tem toupeiras." << endl;
    cout << "As toupeiras são ilustradas por " << RED << "O" << RESET << "." << endl;
    cout << "Ao acertar uma toupeira, você verá um " << GREEN << "X " << RESET << "na posição em que acertou." << endl;
    cout << "As toupeiras não querem que você às acerte, elas se movem de um casa para a outra!" << endl;
    cout << "Caso você acerte uma toupeira, ela vai se mover para outra casa." << endl;

    cout << "As teclas relativas a cada casa do tabuleiro são mostradas abaixo:" << endl;
    cout << YELLOW << "|" << RESET << "Q" << YELLOW << "||" << RESET << "W" << YELLOW << "||"  << RESET << "E" << YELLOW << "|" << endl;
    cout << YELLOW << "|" << RESET << "A" << YELLOW << "||" << RESET << "S" << YELLOW << "||"  << RESET << "D" << YELLOW << "|" << endl;
    cout << YELLOW << "|" << RESET << "Z" << YELLOW << "||" << RESET << "X" << YELLOW << "||"  << RESET << "C" << YELLOW << "|" << RESET << endl;

    cout << "Voce tem " << TEMPO_LIMITE_SEGUNDOS << " segundos para acertar o maximo de toupeiras que conseguir, boa sorte!" << endl;
    cout << "Pressione ENTER para iniciar o jogo." << endl;
    scanf("%c", &c);
}