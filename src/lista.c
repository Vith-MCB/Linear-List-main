#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

#define FINAL_DA_LISTA -1
#define INICIO_DA_LISTA -1
#define INVALIDO -1
#define VALOR_INICIAL 0
#define NENHUM_ELEMENTO 0
#define TRUE 1
#define FALSE 0
#define UM 1
#define ELEMENTO_INICIAL 0
#define LISTA_VAZIA "Lista Vazia!\n"
#define PRINT_ELEMENTO "\n\nPosicao elemento = %d\nPID = %d\nant = %d | prox = %d\n"

/*
 * Essa função é usada para inicializar uma lista. Primeiramente ocorre alocações na memória do array contido nessa
 * estrutura. Após a alocação são inicializadas "Celulas" com cursores predefinidos aos quais
 * apontam para uma próxima célula e uma célula anterior, esses cursores serão posições no array.
 * Então essas "Celulas" são colocadas no array.
 * Há também a inicialização de valores iniciais para as variáveis da estrutura "TLista".
 */
void inicializa_lista(TLista *lista, unsigned int tamanho)
{
    // Alocando espaço na memória para o array que compõe a estrutura lista (tamanho informado pelo usuário).
    lista->celulas = (struct TCelula *) malloc(tamanho * sizeof(TCelula));

    // Inicialização das células vazias definindo os cursores iniciais para cada uma delas.
    // Um cursor apontará para a próxima célula e o outro apontará para a célula anterior.
    // Extremidades são iguais a "-1".
    for (int posicao = VALOR_INICIAL; posicao < tamanho; posicao++)
    {
        int posicao_anterior = posicao - UM;
        int posicao_proximo = posicao + UM;
        TCelula celula;

        celula.ant = posicao_anterior;

        if (posicao == (tamanho - UM))
        {
            celula.prox = FINAL_DA_LISTA;
        }
        else
        {
            celula.prox = posicao_proximo;
        }

        celula.processo = NULL;
        ((TCelula *) lista->celulas)[posicao] = celula; // Colocando célula no array.
    }

    // Inicializando demais variáveis lista.
    lista->numCelOcupados = NENHUM_ELEMENTO;
    lista->tamanho = tamanho;
    lista->celulasDisp = NENHUM_ELEMENTO;
}


/*
 * Função utilizada para obter on número atual de células sendo ocupadas na lista.
 */
unsigned int get_numCelOcupados(TLista *lista)
{
    return lista->numCelOcupados;
}


/*
 * Função utilizada para percorrer a lista com intuito de obter a primeira "célula disponível", identificando uma
 * célula como disponível quando o seu processo é nulo. Caso não exista célula disponível "-1" será retornado.
 */
int get_celula_disponivel(TLista *lista)
{
    int celula_disponivel = INVALIDO;
    TCelula *celulas = (TCelula *) lista->celulas;

    for (int i = VALOR_INICIAL; i < lista->tamanho; i++)
    {
        if (celulas[i].processo == NULL)
        {
            celula_disponivel = i;
            break;
        }
    }

    return celula_disponivel;
}


/*
 * Função usada para adicionar um elemento na lista.
 * Primeiramente tentamos achar uma célula disponível (posição no vetor) para adicionar um processo que é gerado pelo
 * método "inicializa_processo()".
 * Como a lista deve se manter ordenada os elementos já são colocados nas posições corretas, sendo as mesmas definidas
 * pelo PID do processo de cada célula. Em outras palavras, os cursores das células serão usados para ordenar as mesmas
 * na lista de forma que o PID esteja em uma ordem crescente.
 */
unsigned int insere_na_lista(TLista *lista)
{
    // Tentando encontrar uma célula disponível.
    int get_primeira_celula_disponivel = get_celula_disponivel(lista);

    // Checando se há célula disponível.
    if (get_primeira_celula_disponivel == INVALIDO)
    {
        return 0;
    }

    // Inicializando processo para adicionar a uma célula.
    TProcesso *processo_para_adicionar = inicializa_processo();
    TCelula *celulas = (TCelula *) lista->celulas;

    // Valores iniciais para inserir um novo elemento.
    // Posição no array do elemento a ser adicionado.
    lista->celulasDisp = get_primeira_celula_disponivel;
    // Colocando o processo na posição disponível encontrada.
    celulas[lista->celulasDisp].processo = processo_para_adicionar;

    // ------------------------------------------- PRIMEIRO ELEMENTO ---------------------------------------------------
    // Se for o primeiro elemento sendo adicionado na lista.
    if (get_numCelOcupados(lista) == NENHUM_ELEMENTO)
    {
        // Como é o primeiro elemento, seus cursores apontarão para "-1".
        celulas[lista->celulasDisp].ant = INICIO_DA_LISTA;
        celulas[lista->celulasDisp].prox = FINAL_DA_LISTA;

        // Como só temos um elemento apontaremos para esse único elemento (neste caso 0).
        lista->primeiro = (int) lista->celulasDisp;
        lista->ultimo = (int) lista->celulasDisp;
    }
    else // -------------------------------------- OUTROS ELEMENTOS ----------------------------------------------------
    {
        // Essa variável é usada para determinar se existe um elemento com o PID maior do que o elemento que iremos
        // adicionar de modo a encontrar uma posição ideal para o elemento.
        // Caso não encontre o valor da variável continuará falso e o elemento será adicionado ao final da lista.
        unsigned int encontrou_posicao = FALSE;
        int elemento_atual = lista->primeiro; // Obtendo primeiro elemento para percorrer a lista.

        // Percorrendo a lista enquanto não chegar no final.
        while (elemento_atual != FINAL_DA_LISTA)
        {
            // Obtendo processo para comparar PID.
            TProcesso *processo_atual = celulas[elemento_atual].processo;

            // Essa condição será verdadeira caso formos inserir o elemento no meio da lista e no início da lista.
            // Em outras palavras quando existir um elemento maior do que o que iremos adicionar.
            if (get_PID(processo_atual) > get_PID(processo_para_adicionar))
            {
                // Como encontramos um elemento com PID maior do que iremos colocar essa variável se torna verdadeira.
                encontrou_posicao = TRUE;

                /// Essas três condições abaixo seguem um padrão de ordenação observadas em um desenho de uma lista nos
                /// quais esses padrões foram encontrados.

                if (celulas[elemento_atual].ant == INICIO_DA_LISTA)
                {
                    // Quando o elemento for assumir a primeira posição na lista.
                    celulas[lista->primeiro].ant = (int) lista->celulasDisp;
                    celulas[lista->celulasDisp].prox = lista->primeiro;
                    celulas[lista->celulasDisp].ant = FINAL_DA_LISTA;
                    lista->primeiro = (int) lista->celulasDisp;
                }
                else if (celulas[elemento_atual].prox == FINAL_DA_LISTA)
                {
                    // Quando o elemento for assumir a penúltima posição na lista.
                    celulas[lista->celulasDisp].prox = celulas[celulas[elemento_atual].ant].prox;
                    celulas[celulas[elemento_atual].ant].prox = (int) lista->celulasDisp;
                    celulas[lista->celulasDisp].ant = celulas[elemento_atual].ant;
                    celulas[lista->ultimo].ant = (int) lista->celulasDisp;
                }
                else
                {
                    // Quando o elemento for assumir qualquer outra posição que não seja a penúltima posição na lista, a
                    // primeira posição na lista e a última posição na lista (desde que essa depende da variável
                    // "encontrou_posicao" como explicado).
                    int anterior = celulas[elemento_atual].ant;
                    celulas[celulas[elemento_atual].ant].prox = (int) lista->celulasDisp;
                    celulas[elemento_atual].ant = (int) lista->celulasDisp;
                    celulas[lista->celulasDisp].ant = anterior;
                    celulas[lista->celulasDisp].prox = elemento_atual;
                }

                break;
            }

            // Trocando o elemento para continuar o loop até (ou não) entrar na condição (percorrendo a lista).
            elemento_atual = celulas[elemento_atual].prox;

        }

        // Essa condição será verdadeira caso o elemento for entrar na última posição da lista.
        if (!encontrou_posicao)
        {
            celulas[lista->celulasDisp].ant = lista->ultimo;
            celulas[lista->ultimo].prox = (int) lista->celulasDisp;
            celulas[lista->celulasDisp].prox = FINAL_DA_LISTA;
            lista->ultimo = (int) lista->celulasDisp;
        }
    }

    // Após adicionar o elemento temos que incrementar o número de células ocupadas.
    lista->numCelOcupados++;
    return 1;
}


// CÓDIGO EM PRODUÇÃO.
/*
 * Essa função é usada para remover um elemento na primeira posição da lista. Ao remover um elemento a célula que o
 * elemento anteriormente ocupava será definida como nula e essa célula passará a ser uma "célula disponível" a qual
 * irá apontar para uma próxima "célula disponível".
 */
unsigned int remove_da_lista(TLista *lista)
{
    TCelula *celulas = (TCelula *) lista->celulas;

    // Checando se a lista está vazia.
    if (get_numCelOcupados(lista) == NENHUM_ELEMENTO)
    {
        return 0;
    }

    // Checando se a célula atual não é a última.
    if (celulas[lista->primeiro].prox != FINAL_DA_LISTA)
    {
        // Liberando o processo na memória.
        free(celulas[lista->primeiro].processo);

        // Colocando o processo como nulo para "setar" como uma célula disponível.
        celulas[lista->primeiro].processo = NULL;

        // Apontando para a próxima célula disponível.
        celulas[lista->primeiro].ant = get_celula_disponivel(lista);

        // Trocando index da célula que vem após a que deletamos para "-1" para identifica-lá como o início da lista.
        if (celulas[celulas[lista->primeiro].prox].prox != FINAL_DA_LISTA)
        {
            celulas[celulas[lista->primeiro].prox].ant = INICIO_DA_LISTA;
        }

        lista->primeiro = celulas[lista->primeiro].prox; // Alterando cursor.
        // Deixando o primeiro elemento como a primeira célula disponível (valor "-1").
        celulas[ELEMENTO_INICIAL].ant = INICIO_DA_LISTA;
    }
    else // Caso e a última célula na lista.
    {
        // Liberando o processo na memória.
        free(celulas[lista->ultimo].processo);

        // Colocando o processo como nulo para "setar" como uma célula disponível.
        celulas[lista->ultimo].processo = NULL;

        // Alterando os cursores.
        lista->primeiro = ELEMENTO_INICIAL;
        lista->ultimo = ELEMENTO_INICIAL;
    }

    // Após remover o elemento temos que decrementar o número de células ocupadas.
    lista->numCelOcupados--;

    return 1;
}


/*
 * Essa função é usada para mostrar informações de cada célula sendo usada na lista percorrendo células, conforme os
 * indexes das mesmas. Devido à ordenação sendo feita quando inserindo um elemento as células mostradas aqui estarão
 * em ordem crescente de PID do processo.
 */
void imprime_conteudo(TLista *lista)
{
    // Caso não haja nenhum elemento na lista a função retorna ela mesma.
    if (get_numCelOcupados(lista) == NENHUM_ELEMENTO)
    {
        printf(LISTA_VAZIA);
        return;
    }

    TCelula *celulas = (TCelula *) lista->celulas;
    int elemento_atual = lista->primeiro; // Usando o primeiro elemento para percorrer os demais elementos do array.

    // Usando loop até chegar ao final da lista.
    while (elemento_atual != FINAL_DA_LISTA)
    {
        printf(PRINT_ELEMENTO,
               elemento_atual, celulas[elemento_atual].processo->PID,
               celulas[elemento_atual].ant,
               celulas[elemento_atual].prox);

        elemento_atual = celulas[elemento_atual].prox; // Trocando para o próximo elemento.
    }
}


/*
 * Função usada para destruir a lista.
 */
void destroi_lista(TLista *lista)
{
    TCelula *celulas = (TCelula *) lista->celulas;

    for (int i = VALOR_INICIAL; i < lista->tamanho; i++)
    {
        if (celulas[i].processo != NULL)
        {
            free(celulas[i].processo);
        }
    }

    free(lista->celulas);
}