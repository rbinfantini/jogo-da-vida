// JV-IJR-Model.cpp - Projeto Jogo da Vida
// 04/11/2025 - Grupo: IJR
// Joao Batistella
// Rafael Infantini
// Igor Elias


#include <stdlib.h>
#include <stdio.h>
#include "JV-IJR-Model.h"


char mundo[60][60];
int dim;
int exibirVizinhasMortas = 1;


tipoCel *pvivo = NULL;
tipoCel *pmorto = NULL;
tipoCel *pvivoprox = NULL;


int totvivo = 0;
int totmorto = 0;
int totvivoprox = 0;


FILE *arquivoLeitura = NULL;


void model_insereLista(tipoCel **cabeca_da_lista, int *contador, int linha, int coluna)
{
    tipoCel *nova_celula = (tipoCel *) malloc(sizeof(tipoCel));
    if (nova_celula == NULL)
    {
        return;
    }
    nova_celula->linha = linha;
    nova_celula->coluna = coluna;
    nova_celula->next = *cabeca_da_lista;
    *cabeca_da_lista = nova_celula;
    (*contador)++;
}


void model_limpaLista(tipoCel **cabeca_da_lista, int *contador)
{
    tipoCel *aux = *cabeca_da_lista;
    tipoCel *proxima_celula;

    while (aux != NULL)
    {
        proxima_celula = aux->next;
        free(aux);
        aux = proxima_celula;
    }

    *cabeca_da_lista = NULL;
    *contador = 0;
}


void model_excluirDaLista(tipoCel **cabeca_da_lista, int *contador, int lin, int col)
{
    tipoCel *atual = *cabeca_da_lista;
    tipoCel *anterior = NULL;

    if (atual == NULL) return;

    while (atual != NULL && (atual->linha != lin || atual->coluna != col))
    {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) return;

    if (anterior == NULL)
    {
        *cabeca_da_lista = atual->next;
    }
    else
    {
        anterior->next = atual->next;
    }

    free(atual);
    (*contador)--;
}


int model_verificarSeExiste(tipoCel *cabeca_da_lista, int lin, int col)
{
    tipoCel *aux = cabeca_da_lista;
    while (aux != NULL)
    {
        if (aux->linha == lin && aux->coluna == col)
        {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}


void model_atualizarMundoMortos()
{
    model_inicializarMundo();
    model_limpaLista(&pmorto, &totmorto);

    tipoCel *auxVivo = pvivo;
    while (auxVivo != NULL)
    {
        if (auxVivo->linha < dim && auxVivo->coluna < dim)
        {
            mundo[auxVivo->linha][auxVivo->coluna] = 'O';
        }
        auxVivo = auxVivo->next;
    }

    auxVivo = pvivo;
    while (auxVivo != NULL)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0) continue;

                int ni = auxVivo->linha + i;
                int nj = auxVivo->coluna + j;

                if (ni >= 0 && ni < dim && nj >= 0 && nj < dim)
                {
                    if (mundo[ni][nj] == '.')
                    {
                        mundo[ni][nj] = '+';

                        if (model_verificarSeExiste(pmorto, ni, nj) == 0)
                        {
                            model_insereLista(&pmorto, &totmorto, ni, nj);
                        }
                    }
                }
            }
        }
        auxVivo = auxVivo->next;
    }
}


void model_inicializarMundo()
{
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            mundo[i][j] = '.';
        }
    }
}


void model_limparMundo()
{
    model_limpaLista(&pvivo, &totvivo);
    model_limpaLista(&pmorto, &totmorto);
    model_limpaLista(&pvivoprox, &totvivoprox);

    model_inicializarMundo();
}


void model_definirCelula(int linha, int coluna)
{
    if (linha >= 0 && linha < dim && coluna >= 0 && coluna < dim)
    {
        int existe = model_verificarSeExiste(pvivo, linha, coluna);

        if (existe == 1)
        {
           model_excluirDaLista(&pvivo, &totvivo, linha, coluna);
        }
        else
        {
            model_insereLista(&pvivo, &totvivo, linha, coluna);
        }
        
        model_atualizarMundoMortos();
    }
}


int model_contaVizinhosVivos(int linha, int coluna)
{
    int vizinhos = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;

            int ni = linha + i;
            int nj = coluna + j;

            if (ni >= 0 && ni < dim && nj >= 0 && nj < dim)
            {
                if (mundo[ni][nj] == 'O')
                {
                    vizinhos++;
                }
            }
        }
    }
    return vizinhos;
}


void model_alternarExibicaoVizinhas()
{
    if (exibirVizinhasMortas == 0)
    {
        exibirVizinhasMortas = 1;
    }
    else
    {
        exibirVizinhasMortas = 0;
    }
}


void model_avancarGeracao()
{
    model_limpaLista(&pvivoprox, &totvivoprox);

    tipoCel *auxVivo = pvivo;
    while (auxVivo != NULL)
    {
        int vizinhos = model_contaVizinhosVivos(auxVivo->linha, auxVivo->coluna);
        if (vizinhos == 2 || vizinhos == 3)
        {
            model_insereLista(&pvivoprox, &totvivoprox, auxVivo->linha, auxVivo->coluna);
        }
        auxVivo = auxVivo->next;
    }

    tipoCel *auxMorto = pmorto;
    while (auxMorto != NULL)
    {
        int vizinhos = model_contaVizinhosVivos(auxMorto->linha, auxMorto->coluna);
        if (vizinhos == 3)
        {
            model_insereLista(&pvivoprox, &totvivoprox, auxMorto->linha, auxMorto->coluna);
        }
        auxMorto = auxMorto->next;
    }

    model_limpaLista(&pvivo, &totvivo);
    pvivo = pvivoprox;
    totvivo = totvivoprox;

    pvivoprox = NULL;
    totvivoprox = 0;

    model_atualizarMundoMortos();
}


char model_obterEstadoCelula(int linha, int coluna)
{
    if (linha >= 0 && linha < dim && coluna >= 0 && coluna < dim)
    {
        return mundo[linha][coluna];
    }
    return '\0';
}


void model_salvarGeracoes()
{
    FILE *f = fopen("geracoes.txt", "a");
    if (f == NULL)
    {
        return; 
    }

    tipoCel *aux = pvivo;
    while (aux != NULL)
    {
        fprintf(f, "%d %d\n", aux->linha, aux->coluna);
        aux = aux->next;
    }
    
    fprintf(f, "-1 -1\n"); 
    
    fclose(f);
}


int model_carregarGeracoes()
{
    // Abre o arquivo para leitura
    FILE *f = fopen("geracoes.txt", "r");
    if (f == NULL)
    {
        return 0; // Arquivo nao existe
    }

    tipoCel *ultimaGeracao = NULL;
    int totUltima = 0;
    
    tipoCel *geracaoSendoLida = NULL;
    int totSendoLida = 0;

    int linha, coluna;

    // Le o arquivo inteiro
    while (fscanf(f, "%d %d", &linha, &coluna) == 2)
    {
        // Se achou o marcador de fim de geracao (-1 -1)
        if (linha == -1 && coluna == -1)
        {
            model_limpaLista(&ultimaGeracao, &totUltima);
            
            ultimaGeracao = geracaoSendoLida;
            totUltima = totSendoLida;
            
            geracaoSendoLida = NULL;
            totSendoLida = 0;
        }
        else
        {
            // E uma coordenada valida, insere na lista
            model_insereLista(&geracaoSendoLida, &totSendoLida, linha, coluna);
        }
    }
    
    fclose(f); // Fecha o arquivo

    model_limpaLista(&geracaoSendoLida, &totSendoLida);

    model_limparMundo();

    pvivo = ultimaGeracao;
    totvivo = totUltima;

    model_atualizarMundoMortos(); 

    return 1; // Sucesso
}