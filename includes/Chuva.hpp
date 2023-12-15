/*
    Este arquivo possui a definição de funções que lidam com a chuva do jogo.
*/

#pragma once

#include "TexturaImagem.hpp"
#include "Player.hpp"

class Chuva {

    public:

        // Construtor da classe.
        Chuva(int rightWall);

        // As dimensões da gota da chuva.
        const int comprimento = 30;
        const int altura = 46;

        // Velocidade máxima da gota da chuva.
        const int velMax = 1;

        // As coordenadas nos eixos X e Y da gota da chuva.
        int posX, posY;

        // Altera a posição da gota da chuva.
        void movimentar(int rightWall, bool *jogoEmExecucao);

        // Compara as posições do jogador e da gota para ver se ouve colisão,
        // caso haja, a variável "jogoEmExecucao" é setada para false.
        void verificarContato(Player *player, int rightWall, bool *jogoEmExecucao);

    private:

        // Velocidade vertical da chuva.
        int velY;
};