/*
    Este arquivo possui a implementação da classe TexturaImagem, que contém os 
    atributos e métodos necessários para gerenciar as texturas de imagens
    usadas no jogo.

    Em termos gerais, esta classe é responsável por inicializar e destruir as 
    texturas usadas. Além de, quando necessário, renderizá-las na tela de jogo.
*/

#include "includes/TexturaImagem.hpp"

// Construtor da classe.
TexturaImagem::TexturaImagem() {
    texturaReal = NULL;

    comprimento = 0;
    altura = 0;
}

// Desaloca memória.
TexturaImagem::~TexturaImagem() {
    free();
}

// Desaloca a textura.
void TexturaImagem::free() {

    if (texturaReal != NULL) {
        SDL_DestroyTexture(texturaReal);

        texturaReal = NULL;

        comprimento = 0;
        altura = 0;
    }
}

int TexturaImagem::getComprimento() {
    return comprimento;
}

int TexturaImagem::getAltura() {
    return altura;
}

// Renderiza as texturas na tela.
void TexturaImagem::renderizar(int eixoX, int eixoY, SDL_Renderer* renderizador) {
    SDL_Rect renderQuad = {eixoX, eixoY, comprimento, altura};
	SDL_RenderCopy(renderizador, texturaReal, NULL, &renderQuad);
}

// Carrega a imagem contida em "path".
bool TexturaImagem::carregarImagem(std::string path, SDL_Renderer* renderizador) {
    
    // Desaloca qualquer imagem que esteja armazenada no objeto.
    free();

    SDL_Texture *texturaNova = NULL;

    // Criando uma superfície contendo a imagem pedida.
    SDL_Surface *superficieCarregada = IMG_Load(path.c_str());
    
    if (superficieCarregada == NULL) {
        printf("ERRO: Não foi possível carregar a imagem %s --> %s\n", path.c_str(), IMG_GetError());
    } else {

        // Apagando pixels transparentes (usado para PNGs).
        SDL_SetColorKey(superficieCarregada, SDL_TRUE, SDL_MapRGB(superficieCarregada->format, 0, 0xFF, 0xFF));

        // Criando uma textura a partir da superfíce carregada anteriormente.
        texturaNova = SDL_CreateTextureFromSurface(renderizador, superficieCarregada);
        if (texturaNova == NULL) {
            printf("ERRO: Não foi possível criar a textura de %s --> %s\n", path.c_str(), SDL_GetError());
        } else {
            comprimento = superficieCarregada->w;
            altura = superficieCarregada->h;
        }

        // Desalocando memória da superfície.
        SDL_FreeSurface(superficieCarregada);
    }

    // Armazenando a textura criado no objeto.
    texturaReal = texturaNova;

    if (texturaReal == NULL) return false;

    return true;
}