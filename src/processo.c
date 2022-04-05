#include <stdlib.h>
#include <time.h>

#include "processo.h"

#define UM 1
#define LIMITE 5

/*
 * Essa função inicializa um processo com PID (inteiro) e prioridade (inteiro entre 1 e 5) aleatórios,
 * além de conter o tempo de criação (retirado da máquina do usuário).
 */
TProcesso *inicializa_processo()
{
    TProcesso *processo = malloc(sizeof *processo);
    processo->PID = UM + rand();
    processo->prioridade = UM + (rand() % LIMITE);
    inicializa_tempo(processo);
}

/*
 * Função usada para inicializar a hora de criação do processo tendo como base o horário na máquina do usuário,
 * atribuindo o mesmo ao processo que foi inicializado.
 * A biblioteca "time.h" está sendo usada para atingir o objetivo especificado.
 */
void inicializa_tempo(TProcesso *processo)
{
    time_t hora_cru;
    struct tm *hora_atual;

    time(&hora_cru);
    hora_atual = localtime(&hora_cru);
    processo->hora = hora_atual;
}

/*
 * Getter de ID. Foi utilizado uma checagem para checar caso o valor seja nulo.
 */
unsigned int get_PID(TProcesso *processo)
{
    return processo->PID;
}

/*
 * Setter de ID.
 */
void set_PID(TProcesso *processo, unsigned int novo_PID)
{
    processo->PID = novo_PID;
}

/*
 * Getter de prioridade.
 */
unsigned int get_prioridade(TProcesso *processo)
{
    return processo->prioridade;
}

/*
 * Setter de prioridade.
 */
void set_prioridade(TProcesso *processo, unsigned int nova_prioridade)
{
    processo->prioridade = nova_prioridade;
}

/*
 * Getter de hora de criação. Usada função "asctime()" da biblioteca "time.h" com formato "Www Mmm dd hh:mm:ss yyyy".
 */
char *get_hora(TProcesso *processo)
{
    return asctime(processo->hora);
}