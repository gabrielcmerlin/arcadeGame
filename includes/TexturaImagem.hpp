/*
    Este arquivo possui a definição da classe TexturaImagem, que contém os 
    atributos e métodos necessários para gerenciar as texturas de imagens
    usadas no jogo.

    Em termos gerais, esta classe é responsável por inicializar e destruir as 
    texturas usadas. Além de, quando necessário, renderizá-las na tela de jogo.
*/

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class TexturaImagem {

    public:

        // Construtor da classe.
        TexturaImagem();

        // Desaloca memória.
        ~TexturaImagem();

        // Desaloca a textura.
        void free();

        int getComprimento();
        int getAltura();

        // Renderiza as texturas na tela.
        void renderizar(int eixoX, int eixoY, SDL_Renderer* renderizador);
        
        // Carrega a imagem contida em "path".
        bool carregarImagem(std::string path, SDL_Renderer* renderizador);

    private:
    
        // Variável que contém a textura criada.
        SDL_Texture* texturaReal;

        // Dimensões da textura.
        int comprimento;
        int altura;
};