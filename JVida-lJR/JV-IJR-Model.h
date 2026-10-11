// JV-IJR-Model.h - Projeto Jogo da Vida
// 11/11/2025 - Grupo: IJR
// Joao Batistella
// Rafael Infantini
// Igor Elias


#ifndef JV_IJR_MODEL_H
#define JV_IJR_MODEL_H


extern char mundo[60][60];         // Matriz do jogo
extern int dim;                    // Dimensao do mundo (definida pelo usuario)
extern int exibirVizinhasMortas;   // Controla a exibicao de vizinhas mortas


typedef struct cel
{
    int linha, coluna;
    struct cel *next;
} tipoCel;


extern tipoCel *pvivo, *pmorto, *pvivoprox;
extern int totvivo, totmorto, totvivoprox;
extern FILE *arquivoLeitura;


void model_inicializarMundo();                          // Inicia as celulas
void model_definirCelula(int linha, int coluna);        // Troca entre viva e morta
void model_limparMundo();                               // Limpa todas as ceeulas do mapa
int model_contaVizinhosVivos(int linha, int coluna);    // Conta os vizinhos vivos de uma celula
void model_alternarExibicaoVizinhas();                  // Alterna a exibicao das vizinhas mortas
char model_obterEstadoCelula(int linha, int coluna);    // Retorna 'O' ou '.' de uma coordenada
void model_avancarGeracao();                            // Avança as geracoes das celulas
void model_atualizarMundoMortos();


void model_insereLista(tipoCel **cabeca_da_lista, int *contador, int linha, int coluna);    // Insere uma celula na lista
void model_limpaLista(tipoCel **cabeca_da_lista, int *contador);                            // Libera memoria e esvazia a lista
void model_excluirDaLista(tipoCel **cabeca_da_lista, int *contador, int lin, int col);      // Exclui uma celula
int model_verificarSeExiste(tipoCel *cabeca_da_lista, int lin, int col);                    // Verifica se a celula ja esta na lista
void model_salvarGeracoes();                                                                // Salva as geracoes em um arquivo .txt
int model_carregarGeracoes();                                                               // Carrega as geracoes para o jogo


#endif
