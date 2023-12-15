/*
    Este arquivo possui a implementação de funções que lidam com a chuva do jogo.
*/

#include "includes/Chuva.hpp"
#include <ctime>
#include <stdio.h>
#include <mutex>

std::mutex semaf_gotaPosX;
std::mutex semaf_gotaPosY;

// Construtor da classe.
Chuva::Chuva(int rightWall) {
    srand((unsigned)time(0));

    posX = std::rand() % rightWall;
    posY = 0;

    velY = 1;
}

// Altera a posição da gota da chuva.
void Chuva::movimentar(int rightWall, bool *jogoEmExecucao) {
    int gotaPosX, gotaPosY;

    while (1) {

        // Acessando as regiões crítica de memória e guardando seus valores
        // em variáveis locais.
        semaf_gotaPosX.try_lock();
        gotaPosX = posX;
        semaf_gotaPosX.unlock();

        semaf_gotaPosY.try_lock();
        gotaPosY = posY;
        semaf_gotaPosY.unlock();
        
        // Movimento de queda da gota até o chão
        if (gotaPosY < 400) {
            semaf_gotaPosY.try_lock();
            posY += velY;
            semaf_gotaPosY.unlock();
        // Gerando nova gota no topo da tela.
        } else {

            semaf_gotaPosX.try_lock();
            posX = std::rand() % rightWall;
            semaf_gotaPosX.unlock();

            semaf_gotaPosY.try_lock();
            posY = 0;
            semaf_gotaPosY.unlock();
        }

        // Jogo para por 2ms. Usado para fazer com que todos os computadores
        // executem o jogo na "mesma velocidade", ou seja, que nenhuma máquina
        // mais potente tenha a dificuldade do jogo (velocidade da chuva)
        // alterada sem intenção.
        SDL_Delay(2);

        if (!(*jogoEmExecucao)) break; 
    }
}

// Compara as posições do jogador e da gota para ver se ouve colisão,
// caso haja, a variável "jogoEmExecucao" é setada para false.
void Chuva::verificarContato(Player *player, int rightWall, bool *jogoEmExecucao) {
    int gotaPosX, gotaPosY;

    while (1) {

        // Acessando as regiões crítica de memória e guardando seus valores
        // em variáveis locais.
        semaf_gotaPosX.try_lock();
        gotaPosX = posX;
        semaf_gotaPosX.unlock();

        semaf_gotaPosY.try_lock();
        gotaPosY = posY;
        semaf_gotaPosY.unlock();

        // Verificando se há colisão da gota com o jogador.
        if((gotaPosX + comprimento) > (*player).posX && gotaPosX < ((*player).posX + (*player).comprimento)){

            if((gotaPosY + altura) > (*player).posY && gotaPosY < ((*player).posY + (*player).altura)) {

                // Caso ouve colisão, colocamos a gota de chuva no
                // topo da tela e numa posição aleatória do eixo X.
                semaf_gotaPosX.try_lock();
                posX = std::rand() % rightWall;
                semaf_gotaPosX.unlock();

                semaf_gotaPosY.try_lock();
                posY = 0;
                semaf_gotaPosY.unlock();

                // Além disso, o jogo é finalizado.
                *jogoEmExecucao = false;

                return;

            } else {
                *jogoEmExecucao = true;
            }
        } 
    }
}