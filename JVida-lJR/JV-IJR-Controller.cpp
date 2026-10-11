// JV-IJR-Controller.c - Projeto Jogo da Vida
// 11/11/2025 - Grupo: IJR
// Joao Batistella
// Rafael Infantini
// Igor Elias


#include <stdio.h>
#include <windows.h>


#include "JV-IJR-Controller.h"
#include "JV-IJR-Model.h"
#include "JV-IJR-View.h"


void controller_iniciar()
{
    char opcao;

    pvivo = NULL;
    pmorto = NULL;
    pvivoprox = NULL;

    totvivo = 0;
    totmorto = 0;
    totvivoprox = 0;
    
    dim = view_solicitarDimensao();
    
    model_inicializarMundo();

    do
    {
        opcao = view_menuPrincipal();
        controller_processarOpcao(opcao);
    } while (opcao != '0');
}


void controller_processarOpcao(char opcao)
{
    int linha, coluna;

    switch (opcao)
    {
        case '1':
        {
            view_solicitarCoordenadas(&linha, &coluna);
            char estadoAtual = model_obterEstadoCelula(linha, coluna);

            if (estadoAtual == '.' || estadoAtual == '+')
            {
                model_definirCelula(linha, coluna);
            }
            else if (estadoAtual == 'O')
            {
                char resposta = view_confirmarExclusao();

                if (resposta == 's')
                {
                    model_definirCelula(linha, coluna);
                }
                else
                {
                    view_apresentaMensagem("Exclusao cancelada");
                }
            }
            break;
        }
        case '2':
        	model_alternarExibicaoVizinhas();
            break;
        case '3':
        	model_limparMundo();
            break;
        case '4':
        {
            int velocidade = view_solicitarVelocidade();
            int numGeracoes = view_solicitarGeracoes();


            for (int i = 0; i < numGeracoes; i++)
            {
                model_avancarGeracao();
                view_apresentarMundo(i + 1, numGeracoes);

                if (velocidade == 0)
                {
                    view_apresentaMensagem("Pressione ENTER para proxima geracao...");
                }
                else
                {
                    if (velocidade == 1)
                    {
                        Sleep(800);
                    }
                    else if (velocidade == 2)
                    {
                        Sleep(400);
                    }
                    else if (velocidade == 3)
                    {
                        Sleep(200);
                    }
                }
            }
            view_apresentaMensagem("Simulacao de geracoes concluida");
            break;
        }
        case '5':
        {
            model_salvarGeracoes();
            view_apresentaMensagem("Geracoes salvas em geracoes.txt");
            break;
        }
        case '6':
        {
            int sucesso = model_carregarGeracoes();

            if (sucesso == 1)
            {
                view_apresentaMensagem("Geracoes carregadas");
            }
            else
            {
                view_apresentaMensagem("Erro! O arquivo nao foi carregado.");
            }

            break;
        }
        case '0':
            view_apresentaMensagem("Saindo...");
            break;
        default:
            break;
    }
}
