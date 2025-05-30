#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include <pthread.h>

typedef struct {
    int id_dispositivo;
    long timestamp;
    int prioridade;
} Pedido;

void inicializar_fila();
void inserir(Pedido p);
Pedido remover();
int repriorizar(int id_dispositivo, int nova_prioridade);

#endif
