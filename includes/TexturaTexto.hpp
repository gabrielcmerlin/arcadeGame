/*
    Este arquivo possui a definição da classe TexturaTexto, que contém os 
    atributos e métodos necessários para gerenciar as texturas de textos
    usados no jogo.

    Em termos gerais, esta classe é responsável por inicializar e destruir as 
    texturas usadas. Além de, quando necessário, renderizá-las na tela de jogo.
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TexturaTexto {

    public:
    
        // Construtor da classe.
        TexturaTexto();

        // Desaloca memória.
        ~TexturaTexto();

        // Desaloca a textura.
        void free();

        int getComprimento();
        int getAltura();

        // Renderiza as texturas na tela.
        void renderizar(int eixoX, int eixoY, SDL_Renderer* renderizador);
        
        // Carrega o texto contido em "path".
        bool carregarTexto(std::string texto, SDL_Color corTexto, SDL_Renderer* renderizador);

        TTF_Font *fonteTexto;

    private:

        // Variável que contém a textura criada;
        SDL_Texture* texturaReal;

        // Dimensões da textura.
        int comprimento;
        int altura;
};