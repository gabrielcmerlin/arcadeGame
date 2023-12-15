/*
    Este arquivo possui a implementação da classe TexturaTexto, que contém os 
    atributos e métodos necessários para gerenciar as texturas de textos
    usados no jogo.

    Em termos gerais, esta classe é responsável por inicializar e destruir as 
    texturas usadas. Além de, quando necessário, renderizá-las na tela de jogo.
*/

#include "includes/TexturaTexto.hpp"

// Construtor da classe.
TexturaTexto::TexturaTexto() {
    texturaReal = NULL;

    fonteTexto = NULL;

    comprimento = 0;
    altura = 0;
}

// Desaloca memória.
TexturaTexto::~TexturaTexto() {
    free();
}

// Desaloca a textura.
void TexturaTexto::free() {

    if (texturaReal != NULL) {
        SDL_DestroyTexture(texturaReal);

        texturaReal = NULL;

        comprimento = 0;
        altura = 0;
    }
}

int TexturaTexto::getComprimento() {
    return comprimento;
}

int TexturaTexto::getAltura() {
    return altura;
}

// Renderiza as texturas na tela.
void TexturaTexto::renderizar(int eixoX, int eixoY, SDL_Renderer* renderizador) {
    SDL_Rect renderQuad = {eixoX, eixoY, comprimento, altura};
	SDL_RenderCopy(renderizador, texturaReal, NULL, &renderQuad);
}

// Carrega o texto contido em "path".
bool TexturaTexto::carregarTexto(std::string texto, SDL_Color corTexto, SDL_Renderer* renderizador) {
    
    // Desaloca qualquer texto que esteja armazenado no objeto.
    free();

    SDL_Texture *texturaNova = NULL;

    // Criando uma superfície contendo o texto pedido.
    SDL_Surface *superficieTexto = TTF_RenderText_Solid(fonteTexto, texto.c_str(), corTexto);
    
    if (superficieTexto == NULL) {
        printf("ERRO: não foi possível renderizar a superfíce do texto --> %s\n", TTF_GetError());
    } else {

        // Criando uma textura a partir da superfíce criada anteriormente.       
        texturaNova = SDL_CreateTextureFromSurface(renderizador, superficieTexto);
        if (texturaNova == NULL) {
            printf("ERRO: Não foi possível criar a textura a partir do texto --> %s\n", SDL_GetError());
        } else {
            comprimento = superficieTexto->w;
            altura = superficieTexto->h;
        }

        // Desalocando memória da superfície.
        SDL_FreeSurface(superficieTexto);
    }

    // Armazenando a textura criado no objeto.
    texturaReal = texturaNova;

    if (texturaReal == NULL) return false;

    return true;
}