#include "lista.h"

/*
 * Funções abstratas relacionadas a arquivos.
 */

void gera_arquivo(unsigned int qtd_operacoes, unsigned int num_arquivo, unsigned int tamanho_lista);

void arquivo_output(char *nome_arquivo, double tempo_gasto);

unsigned int ler_arquivo(TLista *lista, char *nome_arquivo);