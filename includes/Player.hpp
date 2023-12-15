/*
    Este arquivo contém a definição da classe Player, que contém os atributos
    e métodos necessários para gerenciar a movimentação do boneco.

    Em termos gerais, esta classe lê os inputs do jogador e altera a posição do
    boneco na tela conforme o que foi pedido.
*/

#pragma once

#include "TexturaImagem.hpp"

class Player {

    public:
		
		// Construtor da classe.
		Player();

		// As dimensões do boneco do jogador.
		const int comprimento = 100;
		const int altura = 150;

		// Velocidade máxima do boneco.
		const int velMax = 1;

		// Velocidade horizontal do boneco.
		int velX;

		// As coordenadas nos eixos X e Y do boneco.
		int posX, posY;

		// Variável booleana que serve para criarmos a lógica de pegar a camiseta
		// e colocá-la na caixa. Ela é necessária para evitar que a mesma ação seja
		// feita duas vezes seguidas.
		bool camisetaNaMao;

		// Lê os comandos do jogador e altera a velocidade do boneco.
		void lerInput(SDL_Event& e);

		// Altera a posição do boneco.
		void movimentar(int rightWall);

		/*
			Retorno:
				- 1: Está com a camiseta na mão e está perto da caixa
				1: Não está com a camiseta na mão e está perto da camiseta.
				0: Nenhum dos casos anteriores.
		*/
		int verificaPodePegarCamiseta(int leftWall, int rightWall);

		void setCamisetaNaMao(bool novoValor);
};