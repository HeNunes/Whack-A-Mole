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

int main() 
{
    WhackAMole jogo;
    jogo.iniciarJogo();

    return 0;
}