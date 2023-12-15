/*
    Este arquivo possui a definição da classe Jogo, que contém os atributos
    e métodos necessários para gerenciar a execução do jogo criado.

    Em termos gerais, esta classe contém o Loop de jogo e atende ao desejo do
    usuário de reiniciá-lo ou fechá-lo após perder uma partida.
*/

#pragma once

#include "Tela.hpp"
#include "Player.hpp"
#include "Chuva.hpp"

class Jogo {

    public:

        // Construtor da classe.
        Jogo();

        // Inicia o jogo.
        void jogar();
        
        // Desaloca toda a memória usada.
        void encerrar(Tela tela);
    
    private:
    
        int pontuacao;
        
        // Variáveis usadas para controlar o Loop de jogo.
        bool jogoEmExecucao;
        bool temCamiseta;

        // Renderiza as telas inicias (tela de início e de tutorial) de acordo
        // com o desejo do jogador.
        void rodarTelasIniciais(SDL_Event *e, Tela *tela, bool *reiniciarFlag);

        // Renderiza as imagens e controla toda a lógica necessária para que o
        // jogo funcione.
        bool rodarJogo(SDL_Event *e, Tela *tela, Player *jogador, Chuva *chuva);

        // Renderiza a tela final do jogo.
        bool rodarGameOver(SDL_Event *e, Tela *tela, bool *reiniciarJogo);

        // Reseta todas as variáveis para os valores iniciais para que o jogador
        // possa reiniciar seu jogo.
        void reiniciaJogo(Tela *tela, Player *jogador);
};