/*
    Este arquivo possui a definição de funções que lidam ao mesmo tempo com 
    diversas das texturas do jogo, sejam imagens ou textos. Tais funções são 
    importantes para aumentar a abstração do código e facilitar a compreensão
    dos demais arquivo.
*/

#pragma once

#include "TexturaImagem.hpp"
#include "TexturaTexto.hpp"
#include "Player.hpp"
#include "Chuva.hpp"

// Carrega todas as texturas usadas no jogo.
bool carregarImagemTexto(SDL_Renderer* renderizador);

// Atualiza a pontuação do jogador na tela.
void atualizaPontuacao(SDL_Renderer *renderizador, int pontuacao);

// Renderiza, a depender de "flagImg", OU a tela inicial do jogo OU a tela de tutorial.
void carregarTela(SDL_Renderer *renderizador, bool flagImg);

// Renderiza todas as texturas necessárias para a tela de jogo.
void carregarInGameFrame(SDL_Renderer* renderizador, Player p, Chuva c, bool f);

// Renderiza todas as texturas necessárias para a tela de fim de partida.
void carregarLoseFrame(SDL_Renderer *renderizador, int pontuacao);

// Desaloca memória usada por todas as texturas do jogo.
void destruir();