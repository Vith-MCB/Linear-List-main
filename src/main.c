#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "arquivo.h"

#define UM 1
#define ZERO 0
#define EXIT 0
#define FALSO 0
#define VALOR_INICIAL 0
#define TRUE 1
#define INVALIDO -1
#define PRIMEIRA_OPCAO 1
#define SEGUNDA_OPCAO 2
#define MOSTRAR_OPCOES 3
#define VALOR_INVALIDO "\nValor Invalido\n"
#define OPCAO_INVALIDA "\nOpcao Invalida\n"
#define LISTA_CHEIA "\nLista cheia!\n"
#define LISTA_VAZIA "\nLista Vazia!\n"

// Mencionando funções

void mostrar_opcoes();

clock_t inicializa_relogio();

double finaliza_relogio(clock_t tempo_inicial);

void limpar_stdin();

/*
 * Método principal que gera uma aplicação interativa com o usuário de forma a mostrar o usuário as opções e lidar
 * com valores inválidos que o usuário pode entrar.
 */
int main(void)
{
    int loop = TRUE;
    int imprime_lista = TRUE;

    // Usando loop para lidar com input inválidos e repetições.
    while (loop)
    {
        int escolha = INVALIDO;

        printf("\n\nSimulador de sistema de gerenciamento de processos");
        printf("\nDigite a opcao:");
        mostrar_opcoes(); // Mostrando opções.
        if (!scanf("%d", &escolha)) // Recebendo escolha do usuário e lidando com valores inválidos.
        {
            printf(OPCAO_INVALIDA);
            limpar_stdin();
            continue;
        }

        // Usando switch conforme a opção que o usuário escolheu.
        switch (escolha)
        {
            case EXIT: // Opção 0 (sair)
                printf("\nBye :(\n");
                loop = FALSO;
                break;
            case PRIMEIRA_OPCAO: // Opção 1 (Arquivo).
                printf("\nInformacoes de arquivo");
                printf("\n[1] Criar\n[2] Ler Arquivo\n");
                if (!scanf("%d", &escolha))
                {
                    printf(OPCAO_INVALIDA);
                    limpar_stdin();
                    break;
                }

                // Opcão para criar arquivo.
                if (escolha == PRIMEIRA_OPCAO)
                {
                    // Definido variáveis.
                    int qtd_operacoes = INVALIDO;
                    int num_arquivo;
                    int tamanho_lista;

                    // --------------- Recebendo valores e checando se os mesmos são inválidos -------------------------
                    printf("\nDigite o numero do arquivo que deseja criar:\n");
                    if (!scanf("%d", &num_arquivo) || num_arquivo < 0)
                    {
                        printf(OPCAO_INVALIDA);
                        limpar_stdin();
                        break;
                    }

                    printf("\nDigite o tamanho da lista para o arquivo:\n");
                    if (!scanf("%d", &tamanho_lista) || tamanho_lista < 0)
                    {
                        printf(OPCAO_INVALIDA);
                        limpar_stdin();
                        break;
                    }

                    printf("\nDigite a quantidade de operacoes:\n");
                    if (!scanf("%d", &qtd_operacoes) || qtd_operacoes < 0)
                    {
                        printf(OPCAO_INVALIDA);
                        limpar_stdin();
                        break;
                    }
                    // -------------------------------------------------------------------------------------------------

                    // --------------------------------- Gerando arquivo -----------------------------------------------
                    gera_arquivo(qtd_operacoes, num_arquivo, tamanho_lista);
                    printf("\nArquivo com nome 'teste%02d.txt' gerado!\n", num_arquivo);
                    // -------------------------------------------------------------------------------------------------
                }
                else if (escolha == SEGUNDA_OPCAO)
                {
                    // Definido variáveis.
                    char nome_arquivo[CHAR_MAX];
                    unsigned int sucesso;

                    // ------------------------------ Lendo arquivo ----------------------------------------------------
                    printf("\nDigite o nome do arquivo (sem a extensao):\n");
                    scanf("%s", nome_arquivo);

                    // Inicializando clock.
                    clock_t tempo_inicial = inicializa_relogio();

                    // Inicializando lista que será usada para receber informações do arquivo.
                    TLista lista;

                    // Lendo o arquivo e atribuindo a uma variável para checar se o método foi bem sucedido.
                    sucesso = ler_arquivo(&lista, nome_arquivo);

                    // Checando se ouve algum problem durante a leitura do arquivo.
                    if (!sucesso)
                    {
                        limpar_stdin();
                        break;
                    }

                    // Parando clock e calculando o tempo gasto.
                    double tempo_gasto = finaliza_relogio(tempo_inicial);
                    // -------------------------------------------------------------------------------------------------

                    // ---------------- Mostrando Informações sobre a lista gerada pelo arquivo -----------------------
                    printf("\nTempo em segundos: %0.2lf\n ", tempo_gasto);
                    arquivo_output(nome_arquivo, tempo_gasto); // Gerando arquivo de saída.

                    // Perguntando o usuário se ele deseja ver o conteúdo da lista.
                    printf("\nDeseja imprimir o conteudo da lista?\n[1] Sim [0] Nao\n");
                    if (!scanf("%d", &imprime_lista))
                    {
                        printf(VALOR_INVALIDO);
                        limpar_stdin();
                        break;
                    }

                    // Opção para o usuário decidir se ele deseja printar a lista.
                    if (imprime_lista == UM)
                    {
                        imprime_conteudo(&lista);
                    }
                    else if (imprime_lista != FALSO) // Checando o valor é inválido.
                    {
                        printf(VALOR_INVALIDO);
                        limpar_stdin();
                        break;
                    }
                    destroi_lista(&lista);
                    // -------------------------------------------------------------------------------------------------
                }
                else // Caso a opção for inválida.
                {
                    printf(OPCAO_INVALIDA);
                    limpar_stdin();
                    break;
                }
                break;
            case SEGUNDA_OPCAO: // Opção 2 (valores vindos do usuário)
                // --------------------- Recebendo valores do usuário e aplicando eles na lista ------------------------
                printf("\nInsercao de valores pelo usuario\n");
                int tamanho_lista;

                // Recebendo tamanho da lista e lidando com valores inválidos.
                printf("\nDigite o tamanho da lista: \n");
                if (!scanf("%d", &tamanho_lista) || tamanho_lista < 0)
                {
                    printf(VALOR_INVALIDO);
                    limpar_stdin();
                    break;
                }

                // Inicializando lista.
                TLista lista;
                inicializa_lista(&lista, tamanho_lista);

                // Variável "flag" para o loop.
                int continuar = TRUE;

                // Loop para receber múltiplos valores de remoção ou inserção.
                while (continuar)
                {
                    int insere_ou_remove;
                    int qtd_operacoes;

                    // Recebendo a escolha do usuário (remoção ou inserção) e lidando com valores inválios.
                    printf("\n[0] Insercoes  [1] Remocoes:\n ");
                    if (!scanf("%d", &insere_ou_remove))
                    {
                        printf(VALOR_INVALIDO);
                        limpar_stdin();
                        continue;
                    }

                    // Opção se o usuário escolher inserção.
                    if (insere_ou_remove == ZERO)
                    {
                        printf("\nQuantidade de insercoes:\n ");
                        if (!scanf("%d", &qtd_operacoes) || qtd_operacoes < 0)
                        {
                            printf(VALOR_INVALIDO);
                            limpar_stdin();
                            continue;
                        }

                        clock_t tempo_inicial = inicializa_relogio();

                        // Usado para detectar se a lista estiver cheia após a realização da operação.
                        unsigned int resultado;
                        unsigned int qtd_insercoes = 0;

                        for (int i = VALOR_INICIAL; i < qtd_operacoes; i++)
                        {
                            resultado = insere_na_lista(&lista);
                            qtd_insercoes += resultado;
                        }

                        // Checando se a lista está cheia baseado no valor da última operação.
                        if (!resultado)
                        {
                            printf(LISTA_CHEIA);
                        }

                        printf("\n%d insercoes concluidas com sucesso.\n", qtd_insercoes);
                        printf("\nTempo em segundos: %0.2lf\n ", finaliza_relogio(tempo_inicial));

                        printf("\nDeseja imprimir o conteudo da lista?\n[1] Sim [0] Nao\n");
                        if (!scanf("%d", &imprime_lista))
                        {
                            printf(VALOR_INVALIDO);
                            limpar_stdin();
                            continue;
                        }

                        if (imprime_lista == UM)
                        {
                            imprime_conteudo(&lista);
                        }
                        else if (imprime_lista != FALSO) // Checando o valor é inválido.
                        {
                            printf(VALOR_INVALIDO);
                            limpar_stdin();
                            continue;
                        }
                    }
                    else if (insere_ou_remove == UM) // Opção se o usuário escolher remoção.
                    {
                        printf("\nQuantidade de remocoes:\n ");
                        if (!scanf("%d", &qtd_operacoes) || qtd_operacoes < 0)
                        {
                            printf(VALOR_INVALIDO);
                            limpar_stdin();
                            continue;
                        }

                        clock_t tempo_inicial = inicializa_relogio();

                        // Usado para detectar se a lista estiver vazia após a realização da operação.
                        unsigned int resultado;
                        unsigned int qtd_remocoes = 0;

                        for (int i = VALOR_INICIAL; i < qtd_operacoes; i++)
                        {
                            resultado = remove_da_lista(&lista);
                            qtd_remocoes += resultado;
                        }

                        // Checando se a lista está vazia baseado no valor da última operação.
                        if (!resultado)
                        {
                            printf(LISTA_VAZIA);
                        }

                        printf("\n%d remocoes concluidas com sucesso.\n", qtd_remocoes);
                        printf("\nTempo em segundos: %0.2lf\n ", finaliza_relogio(tempo_inicial));

                        // Perguntando se o usuário deseja imprimir conteúdo da lista.
                        printf("\nDeseja imprimir o conteudo da lista?\n[1] Sim [0] Nao\n");
                        if (!scanf("%d", &imprime_lista)) // Checando se o valor é inválido.
                        {
                            printf(VALOR_INVALIDO);
                            limpar_stdin();
                            continue;
                        }

                        if (imprime_lista == UM)
                        {
                            imprime_conteudo(&lista);
                        }
                        else if (imprime_lista != FALSO) // Checando o valor é inválido.
                        {
                            printf(VALOR_INVALIDO);
                            limpar_stdin();
                            continue;
                        }
                    }
                    else
                    {
                        printf(OPCAO_INVALIDA);
                        limpar_stdin();
                        continue;
                    }

                    // Recebendo escolha do usuário para decidir se ele quer realizar mais operações.
                    printf("\nAdicionar mais insersoes ou remocoes?\n");
                    printf("\n[1] Sim [0] Nao\n");
                    if (!scanf("%d", &continuar)) // Checando se o valor digitado é valido.
                    {
                        printf(OPCAO_INVALIDA);
                        limpar_stdin();
                    }

                    if (!continuar) // Parar o loop.
                    {
                        continuar = FALSO;
                    }
                    else if (continuar != UM) // Continuar o loop.
                    {
                        printf(OPCAO_INVALIDA);
                        continuar = TRUE;
                        limpar_stdin();
                    }
                }
                destroi_lista(&lista);
                // -----------------------------------------------------------------------------------------------------
                break;
            case MOSTRAR_OPCOES: // Opção 3 (mostrar opções).
                mostrar_opcoes();
                break;
            default: // Valor inválido do usuário.
                printf(OPCAO_INVALIDA);
                limpar_stdin();
                break;
        }
    }

    return ZERO;
}


/*
 * Esse método é usado para descrever as opções que o usuário pode escolher, por meio do console.
 */
void mostrar_opcoes()
{
    printf("\n0 - Sair\n"
           "1 - Arquivo\n"
           "2 - Digitar valores para teste\n"
           "3 - Mostrar opcoes\n");
}


/*
 * Função usada para limpar o "stdin" para evitar problemas com "scanf()" dentro de loops.
 */
void limpar_stdin(void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


/*
 * Função usada para iniciar o clock.
 */
clock_t inicializa_relogio(void)
{
    clock_t tempo_inicial = clock();

    return tempo_inicial;
}


/*
 * Função usada para finalizar o clock e calcular o tempo total.
 */
double finaliza_relogio(clock_t tempo_inicial)
{
    clock_t tempo_final = clock();
    double tempo_gasto = (double) (tempo_final - tempo_inicial) / CLOCKS_PER_SEC;

    return tempo_gasto;
}