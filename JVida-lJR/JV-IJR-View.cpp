// JV-IJR-View.cpp - Projeto Jogo da Vida
// 11/11/2025 - Grupo: IJR
// Joao Batistella
// Rafael Infantini
// Igor Elias


#include <stdio.h>
#include <stdlib.h>


#include "JV-IJR-View.h"
#include "JV-IJR-Model.h"


void view_apresentaMensagem(const char mens[])
{
    printf("\n%s\n", mens);
    printf("Pressione ENTER para continuar...");
    fclear();
}


void view_apresentarMundo(int geracaoAtual, int totalGeracoes) // Apresenta o mapa do jogo
{
    view_limpaTela();
    
    if (geracaoAtual > 0)
	{
    printf("=== MAPA DO JOGO DA VIDA - GERACAO %d de %d ===\n", geracaoAtual, totalGeracoes);
	}
	
	else
	{
    printf("=== MAPA DO JOGO DA VIDA ===\n");
	}
    printf("   ");

    for (int j = 0; j < dim; j++)
    {
        printf(" %02d", j);
    }

    printf("\n");
    
    for (int i = 0; i < dim; i++)
    {
        printf("%02d ", i); // Imprime o numero da linha atual

        for (int j = 0; j < dim; j++)
        {
            char celula = mundo[i][j];
            
            if (exibirVizinhasMortas == 0 && celula == '+') // Se a opcao de exibir as celulas mortas estiver DESATIVADA...
            {
               printf(" . ");
            }
            else // Se a celula estiver viva ('O')
            {
                printf(" %c ", celula);
            }
        }
        printf("\n");
    }

    printf("\n");

    printf("Lista de vivos (%d): ", totvivo);

    tipoCel *aux = pvivo;

    while (aux != NULL)
    {
        printf("(%d,%d) ", aux->linha, aux->coluna);
        aux = aux->next;
    }
    printf("\n");

    printf("Lista de vizinhas-mortas (%d): ", totmorto);

    aux = pmorto;

    while (aux != NULL)
    {
        printf("(%d,%d) ", aux->linha, aux->coluna);
        aux = aux->next;
    }
    
    printf("\n");

}


int view_solicitarDimensao()
{
    int d;
    int entrada;

    while(1)
    {
        view_limpaTela();
        printf("=================================\n");
        printf("    PROJETO JOGO DA VIDA - IJR   \n");
        printf("=================================\n\n");
        printf("Defina as dimensoes do mundo (entre 10 e 60): ");

        entrada = scanf("%d", &d);
        
        fclear();

        if (entrada != 1) // Verifica se a entrada e com numeros
        {
            printf("Entrada invalida. Digite com numeros.");
            fclear();
        }
        else if (d < 10 || d > 60) // Verifica o intervalo da entrada
        {
            printf("Intervalo invalido. Deve ser entre 10 e 60.");
            fclear();
        }
        else // Entrada valida
        {
            break;
        }

    }

    return d;
}


char view_menuPrincipal()
{
    char op;
    do
    {
        view_limpaTela();
        view_apresentarMundo(0,0);
        printf("\n--- MENU JOGO DA VIDA ---\n");
        printf("1. Inserir/Remover celula\n");
        printf("2. Mostrar/Esconder vizinhos mortos\n");
        printf("3. Limpar mapa\n");
        printf("4. Iniciar simulacao\n");
        printf("5. Salvar geracao atual\n");
        printf("6. Carregar geracoes\n");
        printf("0. Sair\n");
        printf("\nOpcao: ");
        scanf(" %c", &op);
        fclear();
        
        if (op >= '0' && op <= '6')
        {
            break;
        }

        printf("Entrada invalida!\n");
        printf("Pressione ENTER");
        fclear();
        
    } while (1);

    return op;
}


void view_solicitarCoordenadas(int *linha, int *coluna)
{
    int entrada;

    while(1)
    {
        printf("Digite a linha (0 a %d): ", dim - 1);
        entrada = scanf("%d", linha);
        fclear();

        if (entrada != 1) // Verifica se a entrada e com numeros
        {
            printf("Entrada invalida. Digite com numeros.");
            fclear();
        }
        else if (*linha < 0 || *linha > dim - 1) // Verifica o intervalo da entrada
        {
            printf("Intervalo invalido. Deve ser entre 0 e %d.", dim - 1);
            fclear();
        }
        else
        {
            break;
        }
    }

    while(1)
    {
        printf("Digite a coluna (0 a %d): ", dim - 1);
        entrada = scanf("%d", coluna);
        fclear();

        if (entrada != 1) // Verifica se a entrada e com numeros
        {
            printf("Entrada invalida. Digite com numeros.");
            fclear();
        }
        else if (*coluna < 0 || *coluna > dim - 1) // Verifica o intervalo da entrada
        {
            printf("Intervalo invalido. Deve ser entre 0 e %d.", dim - 1);
            fclear();
        }
        else
        {
            break;
        }
    }
}


void view_limpaTela()
{
    system("cls");
}


void fclear()
{
    char carac;
    while ((carac = fgetc(stdin)) != EOF && carac != '\n') {}
}


int view_solicitarGeracoes()
{
    int d;
    int entrada;

    while(1)
    {
        view_limpaTela();
        printf("Defina o numero de geracoes: ");

        entrada = scanf("%d", &d);
        
        fclear();

        if (entrada != 1) // Verifica se a entrada e com numeros
        {
            printf("Entrada invalida. Digite com numeros.");
            printf("Digire ENTER...");
            fclear();
        }
        else if (d <= 0) // Verifica se a entrada e um numero positivo
        {
            printf("Entrada invalida. Digite um numero positivo.");
            printf("Digite ENTER...");
            fclear();
        }
        else
        {
        	break; // Entrada valida
		}
    }
    return d;
}


int view_solicitarVelocidade()
{
    int d;
    int entrada;

    while(1)
    {
        view_limpaTela();
        printf("Defina a velocidade da simulacao: \n\n");

        printf("0. Passo a passo\n");
        printf("1. Lento\n");
        printf("2. Medio\n");
        printf("3. Rapido\n\n");

        entrada = scanf("%d", &d);
        
        fclear();

        if (entrada != 1) // Verifica se a entrada e com numeros
        {
            printf("Entrada invalida. Digite com numeros.");
            printf("Digite ENTER...");
            fclear();
        }
        else if (d < 0 || d > 3) // Verifica se a entrada e um numero positivo
        {
            printf("Entrada invalida.");
            printf("Precione ENTER...");
            fclear();
        }
        else
        {
        	break; // Entrada valida
		}
    }
    return d;
}


char view_confirmarExclusao()
{
    char resposta;
    while(1)
    {
        view_limpaTela();
        printf("\n--- CONFIRMACAO ---\n");
        printf("Excluir celula viva.\n");
        printf("Tem certeza? (s/n): ");

        scanf(" %c", &resposta);
        fclear();

        if (resposta == 's' || resposta == 'S' || resposta == 'n' || resposta == 'N')
        {
            break; // Entrada valida
        }
        else
        {
            printf("\nOpcao invalida. Digite 's' para sim ou 'n' para nao.\n");
            printf("Pressione ENTER para tentar novamente...");
            fclear();
        }
    }

    // Padroniza a resposta para minúscula
    if (resposta == 'S') return 's';
    if (resposta == 'N') return 'n';
    return resposta;
}
