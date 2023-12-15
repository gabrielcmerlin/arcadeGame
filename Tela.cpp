/*
    Este arquivo contém a implementação da classe Tela, que contém os atributos
    e métodos necessários para gerenciar a tela do jogo.

    Em termos gerais, esta classe inicializa e destrói a tela de jogo.
*/

#include "includes/Tela.hpp"

#include <stdio.h>
#include <stdlib.h>

// Construtor da classe.
Tela::Tela() {
    renderizador = (SDL_Renderer **) malloc(1 * sizeof(SDL_Renderer *));
}

// Cria uma tela de jogo e abre-a.
bool Tela::inicializarTela() {

    // Variável de controle usada para saber se a inicialização da tela deu certo.
    bool sucesso = true;

    // Inicializando a biblioteca SDL.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("ERRO: SDL não pode ser inicializado --> %s\n", SDL_GetError());
        sucesso = false;
    } else {

        // Ativando o filtro para texturas.
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("WARNING: Filtro de texturas não foi ativado\n");
        }

        // Criando janela.
        janela = SDL_CreateWindow("Ajude o Floquinho!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, TELA_COMPRIMENTO, TELA_ALTURA, SDL_WINDOW_SHOWN); 
        
        if (janela == NULL) {
            printf("ERRO: Falha ao criar nova janela --> %s\n", SDL_GetError());
            sucesso = false;
        } else {

            // Criando renderizador.
            SDL_Renderer *rend = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
            *renderizador = rend;

            if (*renderizador == NULL) {
                printf("ERRO: Falha ao criar renderizador --> $s\n", SDL_GetError());
                sucesso = false;
            } else {

                // Inicializando a extensão para imagens da biblioteca SDL.
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("ERRO: Falha ao inicializar SDL_Image --> %s\n", IMG_GetError());
                    sucesso = false;
                }

                // Inicializando a extensão para textos da biblioteca SDL.
                if(TTF_Init() == -1) {
                    printf("ERRO: Falha ao inicializar SDL_ttf --> %s\n", TTF_GetError());
                    sucesso = false;
                }
			}
        }
    }
    
    return sucesso;
}

// Desaloca toda a memória usada.
void Tela::destruir() {
    SDL_DestroyRenderer(*renderizador);
	SDL_DestroyWindow(janela);
	
    janela = NULL;
	*renderizador = NULL;

    // Desativando a biblioteca SDL e suas extensões (imagem e texto).
	SDL_Quit();
    IMG_Quit();
	TTF_Quit();
}