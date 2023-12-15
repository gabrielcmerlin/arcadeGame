/*
    Este módulo possui a definição da classe Tela, que contém os atributos
    e métodos necessários para gerenciar a tela do jogo.

    Em termos gerais, esta classe inicializa e destrói a tela de jogo.
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Tela {

    public:

        // Construtor da classe.
        Tela();

        // Cria uma tela de jogo e abre-a.
        bool inicializarTela();

        // Desaloca toda a memória usada.
        void destruir();

        // Objeto que renderiza a tela de jogo.
        SDL_Renderer** renderizador = NULL;

        // Posição no eixo X da qual o boneco do jogador não pode ultrapassar
        // senão sua textura ficará fora da tela.
        int leftWall = 5;
        int rightWall = 610;

    private:
    
        // Resolução da tela de jogo.
        const int TELA_COMPRIMENTO = 640;
        const int TELA_ALTURA = 480;

        // Janela de jogo (tela).
        SDL_Window* janela = NULL;
};