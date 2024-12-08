#ifndef __LISTA_H
#define __LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include "memoria.h"

// Lista encadeada simples.
typedef struct lista {
    int dado;
    struct lista *prox;
} LISTA;

LISTA *init_lista();
void inserir(LISTA *lista, int dado);
void remover(LISTA **lista, int dado);
void imprimir(LISTA *lista);
void excluir(LISTA *lista);
void imprimir_memoria();

#endif