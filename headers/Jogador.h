#ifndef JOGADOR_H
#define JOGADOR_H

// Classe do Jogador
class Jogador 
{
    private:
        char escolha;    // Posição do tabuleiro escolhida (lida da stdin)
        int linha;    
        int coluna;
        bool pos_valida; // Sinaliza se a posicao lida existe no jogo

    public:
        Jogador(); // Construtor

        // Le a posição escolhida pelo jogador
        void input();
        
        void ocupa_posicao_jogador();
        void desocupa_posicao_jogador();
        char get_escolha() const;
        int get_linha() const;
        int get_coluna() const;
        bool posicao_valida() const;
};

#endif