#ifndef TOUPEIRA_H
#define TOUPEIRA_H

// Classe da Toupeira
class Toupeira 
{
    private:
        int linha;  
        int coluna;
        int id;

    public:
        Toupeira(int i); // Construtor

        void ocupa_posicao_toupeira();
        void desocupa_posicao_toupeira();

        // Escolhe uma nova posição desocupada do tabuleiro
        void escolhe_posicao();
        
        // Move a toupeira de uma casa para outra
        void mover_toupeira();
        
        // Funções "get":
        int get_id() const;
        int get_linha() const; 
        int get_coluna() const; 
};

#endif