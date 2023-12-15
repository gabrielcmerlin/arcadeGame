/*
    Este arquivo contém a implementação da classe Jogo, que contém os atributos
    e métodos necessários para gerenciar a execução do jogo.

    Em termos gerais, esta classe contém o Loop de jogo e atende ao desejo do
    usuário de reiniciá-lo ou fechá-lo após perder uma partida.
*/

#include "includes/Jogo.hpp"
#include "includes/Player.hpp"
#include "includes/Chuva.hpp"
#include "includes/gerenciarTexturas.hpp"
#include <thread>

// Construtor da classe.
Jogo::Jogo() {
    pontuacao = 0;
    jogoEmExecucao = true;
    temCamiseta = true;
}

// Inicia o jogo.
void Jogo::jogar() {

    // Criando uma tela, um jogador e inicializando-os.
    Tela tela = Tela();
    Player jogador = Player();
    Chuva chuva = Chuva(tela.rightWall);
    TexturaImagem camiseta;

    if(!tela.inicializarTela()) {
        printf("Falha ao inicializar tela de jogo.\n");
    } else {
        
        // Variável usada para controlar se o jogo será reinicializado ou
        // fechado, de acordo com o desejo do usuário, após o fim de uma partida.
        bool reiniciarFlag = true;

        // Criando e inicializando todas as texturas (imagens e textos) usadas.
        if (!carregarImagemTexto(*(tela.renderizador))) {
            printf("Falha ao carregar imagens e textos.\n");
        } else {

            // Usada para manipular os eventos do jogo. Em geral, usada para
            // tratar os inputs do jogador.
            SDL_Event e;
           
            rodarTelasIniciais(&e, &tela, &reiniciarFlag);

            while (reiniciarFlag) {
                if(!rodarJogo(&e, &tela, &jogador, &chuva)) break;

                if(!rodarGameOver(&e, &tela, &reiniciarFlag)) break;

                reiniciaJogo(&tela, &jogador);
            }
        }

        // Liberando memória.
        encerrar(tela);
    }
}

// Desaloca toda a memória usada.
void Jogo::encerrar(Tela tela) {
    
    // Desalocando as texturas.
    destruir();

    // Desalocando a tela.
    tela.destruir();
}

// Renderiza as telas inicias (tela de início e de tutorial) de acordo
// com o desejo do jogador.
void Jogo::rodarTelasIniciais(SDL_Event *e, Tela *tela, bool *reiniciarFlag) {
    bool perdeu = false, flagImg = true;

    while(!perdeu) {

        // Lendo inputs do jogador.
        while(SDL_PollEvent(e) != 0) {

            // Jogador tentou fechar a aba jogo.
            if ((*e).type == SDL_QUIT) {
                *reiniciarFlag = false;
                perdeu = true;
            } 
            else if ((*e).type == SDL_KEYDOWN) { // Jogador apertou uma tecla.
                
                switch((*e).key.keysym.sym) {

                    // Tecla ENTER mostra a tela de tutorial do jogo.
                    case SDLK_RETURN:
                    flagImg = !flagImg;
                    break;

                    // Tecla SPACE fecha o jogo.
                    case SDLK_SPACE:
                    if (flagImg == true) {
                        perdeu = true;
                    }

                    break;
                }
            }
        }

        carregarTela(*((*tela).renderizador), flagImg);
    }
}

// Renderiza as imagens e controla toda a lógica necessária para que o
// jogo funcione.
bool Jogo::rodarJogo(SDL_Event *e, Tela *tela, Player *jogador, Chuva *chuva) {
    bool perdeu = false;

    std::thread t_chuva(&Chuva::movimentar, chuva, (*tela).rightWall, &jogoEmExecucao);
    std::thread t_contato(&Chuva::verificarContato, chuva, jogador, (*tela).rightWall, &jogoEmExecucao);

    // Loop de jogo.
    while(!perdeu) {

        // Lendo inputs do jogador.
        while(SDL_PollEvent(e) != 0) {

            // Jogador tentou fechar a aba jogo.
            if ((*e).type == SDL_QUIT) {
                return false;
            }
            else if((*e).type == SDL_KEYDOWN) // Jogador apertou uma tecla.
            {

                switch((*e).key.keysym.sym)
                {
                    // Tecla SPACE realiza alguma ação no jogo.
                    case SDLK_SPACE:
                    
                    // Verificando se o jogador pode pegar uma camiseta ou se pode entregá-la.
                    int verificaRetorno = (*jogador).verificaPodePegarCamiseta((*tela).leftWall , (*tela).rightWall);

                    // Caso tentou colocar a camiseta na caixa...
                    if (verificaRetorno == -1) {
                        // Tirando a camiseta da posse do jogador.
                        (*jogador).setCamisetaNaMao(false);

                        // Alterando flag de presença da camiseta no jogo para que possamos renderizá-la.
                        temCamiseta = true;

                        pontuacao++;
                        atualizaPontuacao(*((*tela).renderizador), pontuacao);
                    // Caso tentou pegar camiseta...
                    } else if (verificaRetorno == 1) {
                        // Colocando a camiseta na posse do jogador.
                        (*jogador).setCamisetaNaMao(true);

                        // Alterando flag de presença da camiseta no jogo para que não a renderizemos.
                        temCamiseta = false;
                    }

                    break;
                }
            }

            (*jogador).lerInput((*e));
        }
        
        (*jogador).movimentar((*tela).rightWall);

        carregarInGameFrame(*((*tela).renderizador), (*jogador), (*chuva), temCamiseta);

        perdeu = !jogoEmExecucao;
    }

    t_chuva.join();
    t_contato.join();

    return true;
}

// Renderiza a tela final do jogo.
bool Jogo::rodarGameOver(SDL_Event* e, Tela* tela, bool *reiniciarFlag) {
    bool perdeu = false;            

    // Carregando a tela de derrota.
    carregarLoseFrame(*((*tela).renderizador), pontuacao);
    
    // Loop para deixar a tela de derrota carregada até o jogador escolher uma
    // das opções: Reiniciar o jogo ou sair dele.
    while(!perdeu) {

        // Lendo inputs do jogador.
        while(SDL_PollEvent(e) != 0) {

            // Jogador tentou fechar a aba jogo.
            if ((*e).type == SDL_QUIT) {
                return false;
            } else if ((*e).type == SDL_KEYDOWN) { // Jogador apertou uma tecla.
                
                switch((*e).key.keysym.sym) {

                    // Tecla ENTER reinicia o jogo.
                    case SDLK_RETURN:
                    *reiniciarFlag = true;
                    perdeu = true;
                    break;

                    // Tecla SPACE fecha o jogo.
                    case SDLK_SPACE:
                    *reiniciarFlag = false;
                    perdeu = true;

                    break;
                }
            }
        }
    }

    return true;
}

// Reseta todas as variáveis para os valores iniciais para que o jogador
// possa reiniciar seu jogo.
void Jogo::reiniciaJogo(Tela *tela, Player *jogador) {
    pontuacao = 0;

    (*jogador).velX = 0;
    (*jogador).camisetaNaMao = false;

    jogoEmExecucao = true;

    temCamiseta = true;
    atualizaPontuacao(*((*tela).renderizador), pontuacao);
}