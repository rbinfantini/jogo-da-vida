// JV-IJR-View.h - Projeto Jogo da Vida
// 11/11/2025 - Grupo: IJR
// Joao Batistella
// Rafael Infantini
// Igor Elias


#ifndef JV_IJR_VIEW_H
#define JV_IJR_VIEW_H


char view_menuPrincipal();                                       // Apresenta o menu do jogo
char view_confirmarExclusao();                                   // Confirma a exclusao
int view_solicitarDimensao();                                    // Pede as dimensoes do mapa
int view_solicitarGeracoes();                                    // Pede o numero de geracoes a serem simuladas
int view_solicitarVelocidade();                                  // Solicita a velocidade desejada
void view_solicitarCoordenadas(int *linha, int *coluna);         // Pede as coordenadas da celula a ser adicionada
void view_apresentarMundo(int geracaoAtual, int totalGeracoes);  // Apresenta o mapa do jogo
void view_apresentaMensagem(const char mens[]);                  // Apresenta as mensagens
void view_limpaTela();                                           // Limpa a tela
void fclear();

#endif
