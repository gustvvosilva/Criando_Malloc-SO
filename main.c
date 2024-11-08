#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "memoria.h"

int main() {

    LISTA *lista = init_lista();

    inserir(lista, 10);
    inserir(lista, 20);
    inserir(lista, 30);
    inserir(lista, 40);
    inserir(lista, 50);

    imprimir(lista);
    imprimir_memoria();

    int *teste = (int *) aloca(sizeof(int));
    *teste = 7;
    imprimir_memoria();

    remover(&lista, 30);

    imprimir(lista);
    imprimir_memoria();

    inserir(lista, 60);
    inserir(lista, 70);
    inserir(lista, 80);
    imprimir(lista);
    imprimir_memoria();

    excluir(lista);
    imprimir_memoria();

    return 0;
}
