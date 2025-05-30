#include "fila_prioridade.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 100

static Pedido fila[TAM_MAX];
static int tamanho = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int pai(int i) { return (i - 1) / 2; }
static int esquerdo(int i) { return 2 * i + 1; }
static int direito(int i) { return 2 * i + 2; }

static void trocar(int i, int j) {
    Pedido temp = fila[i];
    fila[i] = fila[j];
    fila[j] = temp;
}

void inicializar_fila() {
    pthread_mutex_lock(&mutex);
    tamanho = 0;
    pthread_mutex_unlock(&mutex);
}

void inserir(Pedido p) {
    pthread_mutex_lock(&mutex);

    if (tamanho >= TAM_MAX) {
        printf("Fila cheia!\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    int i = tamanho++;
    fila[i] = p;

    while (i > 0 && fila[pai(i)].prioridade < fila[i].prioridade) {
        trocar(i, pai(i));
        i = pai(i);
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

Pedido remover() {
    pthread_mutex_lock(&mutex);

    while (tamanho == 0) {
        pthread_cond_wait(&cond, &mutex);
    }

    Pedido resultado = fila[0];
    fila[0] = fila[--tamanho];

    int i = 0;
    while (1) {
        int maior = i;
        int esq = esquerdo(i);
        int dir = direito(i);

        if (esq < tamanho && fila[esq].prioridade > fila[maior].prioridade)
            maior = esq;
        if (dir < tamanho && fila[dir].prioridade > fila[maior].prioridade)
            maior = dir;

        if (maior == i) break;

        trocar(i, maior);
        i = maior;
    }

    pthread_mutex_unlock(&mutex);
    return resultado;
}

int repriorizar(int id_dispositivo, int nova_prioridade) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < tamanho; i++) {
        if (fila[i].id_dispositivo == id_dispositivo) {
            int old = fila[i].prioridade;
            fila[i].prioridade = nova_prioridade;

            if (nova_prioridade > old) {
                while (i > 0 && fila[pai(i)].prioridade < fila[i].prioridade) {
                    trocar(i, pai(i));
                    i = pai(i);
                }
            } else {
                while (1) {
                    int maior = i;
                    int esq = esquerdo(i);
                    int dir = direito(i);

                    if (esq < tamanho && fila[esq].prioridade > fila[maior].prioridade)
                        maior = esq;
                    if (dir < tamanho && fila[dir].prioridade > fila[maior].prioridade)
                        maior = dir;

                    if (maior == i) break;

                    trocar(i, maior);
                    i = maior;
                }
            }

            pthread_mutex_unlock(&mutex);
            return 1;
        }
    }

    pthread_mutex_unlock(&mutex);
    return 0;
}
