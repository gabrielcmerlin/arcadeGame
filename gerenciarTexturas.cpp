/*
    Este arquivo possui a implementação de funções que lidam ao mesmo tempo com 
    diversas das texturas do jogo, sejam imagens ou textos. Tais funções são 
    importantes para aumentar a abstração do código e facilitar a compreensão
    dos demais arquivo.
*/

#include "includes/gerenciarTexturas.hpp"

// Texturas usadas no jogo.
TexturaImagem floquinho;
TexturaImagem gota;
TexturaImagem telaInicial;
TexturaImagem telaTutorial;
TexturaImagem telaJogo;
TexturaImagem telaFinal;
TexturaImagem camiseta;
TexturaTexto texturaTextoPontuacao;

// Configurações para as texturas de texto.
TTF_Font* fonte = NULL;
SDL_Color corTexto = { 255, 255, 255 };

// Carrega todas as texturas usadas no jogo.
bool carregarImagemTexto(SDL_Renderer* renderizador) {

    // Variável de controle usada para saber se o carregamento das texturas deu certo.
    bool sucesso = true;

    // Carregando as texturas das imagens.
    if (!telaInicial.carregarImagem("images/telaInicial.png", renderizador)) {
        printf("Falha o carregar a textura da tela inicial.\n");
        sucesso = false;
    }
    if (!telaTutorial.carregarImagem("images/tutorial.png", renderizador)) {
        printf("Falha o carregar a textura da tela de tutorial.\n");
        sucesso = false;
    }
    if (!floquinho.carregarImagem("images/floquinho.png", renderizador)) {
        printf("Falha o carregar a textura do Floquinho.\n");
        sucesso = false;
    }
    if (!gota.carregarImagem("images/gota.png", renderizador)) {
        printf("Falha o carregar a textura da Gota.\n");
        sucesso = false;
    }
    if (!telaJogo.carregarImagem("images/telaJogo.bmp", renderizador)) {
        printf("Falha o carregar a textura do tela do jogo.\n");
        sucesso = false;
    }
    if (!telaFinal.carregarImagem("images/telaFinal.png", renderizador)) {
        printf("Falha o carregar a textura da tela final.\n");
        sucesso = false;
    }
    if (!camiseta.carregarImagem("images/gameShirt.png", renderizador)) {
        printf("Falha o carregar a textura da camiseta.\n");
        sucesso = false;
    }

    // Abrindo a fonte escolhida.
    fonte = TTF_OpenFont("fonts/MilkyNice.ttf", 60);
    if (fonte == NULL) {
        printf("Falha ao carregar a fonte do texto.\n");
        sucesso = false;
    } else {

        // Carregando a textura do texto.
        texturaTextoPontuacao.fonteTexto = fonte;
        if (!texturaTextoPontuacao.carregarTexto("0", corTexto, renderizador)) {
            printf("Falha ao carregar a textura do texto.\n");
            sucesso = false;
        }
    }

    return sucesso;
}

// Atualiza a pontuação do jogador na tela.
void atualizaPontuacao(SDL_Renderer *renderizador, int pontuacao) {
    texturaTextoPontuacao.carregarTexto(std::to_string(pontuacao), corTexto, renderizador);
}

// Renderiza, a depender de "flagImg", OU a tela inicial do jogo OU a tela de tutorial.
void carregarTela(SDL_Renderer *renderizador, bool flagImg) {
    
    // Limpando a tela de jogo das texturas renderizadas anteriormente.
    SDL_RenderClear(renderizador);

    /*
	    FlagImg:
		    true: Carrega a tela inicial.
		    false: Carrega a tela de tutorial.
    */
    if (flagImg) {
        telaInicial.renderizar(0, 0, renderizador);
    } else {
        telaTutorial.renderizar(0, 0, renderizador);
    }

    // Atualizando a tela de jogo com as novas texturas renderizadas.
    SDL_RenderPresent(renderizador);
}

// Renderiza todas as texturas necessárias para a tela de jogo.
void carregarInGameFrame(SDL_Renderer* renderizador, Player jogador, Chuva chuva, bool temCamiseta) {
    // Limpando a tela de jogo das texturas renderizadas anteriormente.
    SDL_RenderClear(renderizador);

    // Renderizando o telaJogo na tela.
    telaJogo.renderizar(0, 0, renderizador);

    if(temCamiseta){
        camiseta.renderizar(520, 320, renderizador);
    }
    
    // Renderizando o texto da pontuação do jogo.
    texturaTextoPontuacao.renderizar(25, 25, renderizador);

    // Renderizando o personagem do jogo.
    floquinho.renderizar(jogador.posX, jogador.posY, renderizador);

    // Renderizando a gota da chuva,
    gota.renderizar(chuva.posX, chuva.posY, renderizador);


    // Atualizando a tela de jogo com as novas texturas renderizadas.
    SDL_RenderPresent(renderizador);
}

// Renderiza todas as texturas necessárias para a tela de fim de partida.
void carregarLoseFrame(SDL_Renderer *renderizador, int pontuacao) {
    
    // Limpando a tela de jogo das texturas renderizadas anteriormente.
    SDL_RenderClear(renderizador);

    // Renderizando a tela branca de telaJogo.
    telaFinal.renderizar(0, 0, renderizador);

    // Criando as strings que serão escritas na tela de fim de partida.
    std::string str2 = std::to_string(pontuacao);

    // Criando as texturas de texto.
    TexturaTexto textStr2;

    // Configurando a fonte das texturas.
    textStr2.fonteTexto = fonte;

    // Carregando os textos das strings para as texturas.
    textStr2.carregarTexto(str2, corTexto, renderizador);

    // Renderizando todas as texturas de texto.
    textStr2.renderizar(300, 145, renderizador);

    // Atualizando a tela de jogo com as novas texturas renderizadas.
    SDL_RenderPresent(renderizador);
}

// Desaloca memória usada por todas as texturas do jogo.
void destruir() {
    floquinho.free();
    gota.free();
    telaJogo.free();
    telaFinal.free();
    camiseta.free();
    texturaTextoPontuacao.free();

    TTF_CloseFont(fonte);
    fonte = NULL;
}