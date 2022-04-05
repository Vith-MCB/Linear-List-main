#include "processo.h"

/*
 * Estrutura abstrata para uma lista de processos ao qual simula processo de uma máquina.
 * A estrutura lista é composta pela estrutura célula onde que abriga um processo (tipo de dado que simula um processo),
 * além de possuir dois "Cursor" que são inteiros usados para interligar Células em que são dispostas em um array na
 * lista.
 * Além da estrutura lista possuir um array de "Celula", a mesma também possui um tamanho (tamanho da lista que será
 * usada pelo usuário), dois "Cursor" que são inteiros usados para apontar para a primeira e última célula na lista,
 * um inteiro que demostra a célula que está atualmente disponível para receber um processo e um inteiro que representa
 * o número de células sendo ocupadas no array.
 */

typedef int Cursor;

typedef struct Celula
{
    TProcesso *processo;
    Cursor prox;
    Cursor ant;
} TCelula;

typedef struct
{
    unsigned int tamanho;
    struct TCelula *celulas;
    Cursor primeiro;
    Cursor ultimo;
    unsigned int celulasDisp;
    unsigned int numCelOcupados;
} TLista;

// Função de inicialização

void inicializa_lista(TLista *lista, unsigned int tamanho);

void destroi_lista(TLista *lista);


// Operações

unsigned int insere_na_lista(TLista *lista);

unsigned int remove_da_lista(TLista *lista);

void imprime_conteudo(TLista *lista);


// Getter

unsigned int get_numCelOcupados(TLista *lista);