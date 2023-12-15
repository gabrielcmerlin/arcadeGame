/*
    Este arquivo contém a implementação da classe Player, que contém os atributos
    e métodos necessários para gerenciar a movimentação do boneco.

    Em termos gerais, esta classe lê os inputs do jogador e altera a posição do
    boneco na tela conforme o que foi pedido.
*/

#include "includes/Player.hpp"

// Construtor da classe.
Player::Player() {
    posX = 250;
    posY = 300;

    velX = 0;

    camisetaNaMao = false;
}

// Lê os comandos do jogador e altera a velocidade do boneco.
void Player::lerInput(SDL_Event& e) {

    // Se uma tecla for pressionada
	if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        // Ajustando a velocidade
        switch(e.key.keysym.sym) {
            case SDLK_LEFT:
                velX -= velMax;
                break;
            case SDLK_RIGHT:
                velX += velMax;
                break;
        }
    }
    // Se uma tecla for liberada
    else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
        // Ajustando a velocidade
        switch( e.key.keysym.sym ) {
            case SDLK_LEFT:
                velX += velMax;
                break;
            case SDLK_RIGHT:
                velX -= velMax;
                break;
        }
    }
}

// além de que o jogo é finalizado.
void Player::movimentar(int rightWall) {
    // Movimentando o boneco para a direita ou esquerda.
    posX += velX;

    // Evitando de o boneco sair das bordas da tela.
    if ((posX < 0) || (posX + comprimento > rightWall)) {
        //Move back
        posX -= velX;
    }
}

/*
	Retorno:
		- 1: Está com a camiseta na mão e está perto da caixa
		1: Não está com a camiseta na mão e está perto da camiseta.
		0: Nenhum dos casos anteriores.
*/
int Player::verificaPodePegarCamiseta(int leftWall, int rightWall) {

	if (posX < leftWall && camisetaNaMao) {
		return -1;
	}

	if (posX > (rightWall - 120) && !camisetaNaMao) {
		return 1;
	}

	return 0;
}

void Player::setCamisetaNaMao(bool novoValor) {
	camisetaNaMao = novoValor;
}